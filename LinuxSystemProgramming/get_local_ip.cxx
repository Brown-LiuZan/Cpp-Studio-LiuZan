#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <string.h>
#include <unistd.h> // socklen_t
#include <ifaddrs.h> // getifaddrs/freeifaddrs
#include <arpa/inet.h> // inet_ntop
#include <netinet/in.h> // struct sockaddr_in[6]

#include <gtest/gtest.h>


using namespace std;

bool IsLoopbackIp(const std::string & ip)
{
    return ip.find("127") == 0u || std::string{"::1"} == ip;
}

int GetHostIpStrings(std::set<std::string> *ipSet, bool needLoopbackIps = true)
{
    constexpr socklen_t MAX_ADDRSTRLEN = INET6_ADDRSTRLEN > INET_ADDRSTRLEN ?
        INET6_ADDRSTRLEN : INET_ADDRSTRLEN;

    if (nullptr == ipSet) return -1;
    ipSet->clear();

    struct ifaddrs * vpIfAddrHead = nullptr;
    if (getifaddrs(&vpIfAddrHead) != 0) return -2;

    struct ifaddrs * vpIfAddrStruct = vpIfAddrHead;
    struct sockaddr * vpSockAddr = nullptr;
    struct sockaddr_in * vpSockAddrV4 = nullptr;
    struct sockaddr_in6 * vpSockAddrV6 = nullptr;
    char vIpStr[MAX_ADDRSTRLEN];
    while (vpIfAddrStruct != nullptr) {
        vpSockAddr = vpIfAddrStruct->ifa_addr;
        if (AF_INET == vpSockAddr->sa_family) {
            vpSockAddrV4 = reinterpret_cast<struct sockaddr_in *>(vpSockAddr);
            if (nullptr == inet_ntop(
                        AF_INET,
                        &vpSockAddrV4->sin_addr.s_addr, // uint32_t
                        vIpStr,
                        INET_ADDRSTRLEN)) {
                return -3;
            }
            if (needLoopbackIps || !IsLoopbackIp(vIpStr)) {
                ipSet->emplace(vIpStr);
            }
        } else if (AF_INET6 == vpSockAddr->sa_family) {
            vpSockAddrV6 = reinterpret_cast<struct sockaddr_in6 *>(vpSockAddr);
            if (nullptr == inet_ntop(
                        AF_INET6,
                        vpSockAddrV6->sin6_addr.s6_addr, // uint8_t[16]
                        vIpStr,
                        INET6_ADDRSTRLEN)) {
                return -4;
            }
            if (needLoopbackIps || !IsLoopbackIp(vIpStr)) {
                ipSet->emplace(vIpStr);
            }
        }
        vpIfAddrStruct = vpIfAddrStruct->ifa_next;
    }

    freeifaddrs(vpIfAddrHead);
    return 0;
}

int GetIfInetAddrs(std::vector<struct ifaddrs> *addrVecV4,
        std::vector<struct ifaddrs> *addrVecV6)
{
    if (nullptr == addrVecV4 && nullptr == addrVecV6) return -1;
    if (nullptr != addrVecV4) addrVecV4->clear();
    if (nullptr != addrVecV6) addrVecV6->clear();

    struct ifaddrs * vpIfAddrHead = nullptr;
    if (getifaddrs(&vpIfAddrHead) != 0) return -2;

    struct ifaddrs * vpIfAddrStruct = vpIfAddrHead;
    struct sockaddr * vpSockAddr = nullptr;
    while (vpIfAddrStruct != nullptr) {
        vpSockAddr = vpIfAddrStruct->ifa_addr;
        if (AF_INET == vpSockAddr->sa_family && nullptr != addrVecV4) {
            addrVecV4->emplace_back(*vpIfAddrStruct);
        } else if (AF_INET6 == vpSockAddr->sa_family && nullptr != addrVecV6) {
            addrVecV6->emplace_back(*vpIfAddrStruct);
        }

        vpIfAddrStruct = vpIfAddrStruct->ifa_next;
    }

    freeifaddrs(vpIfAddrHead);
    return 0;
}

int GetIfInet4Addrs(std::vector<struct ifaddrs> *addrVec)
{
    return GetIfInetAddrs(addrVec, nullptr);
}

int GetIfInet6Addrs(std::vector<struct ifaddrs> *addrVec)
{
    return GetIfInetAddrs(nullptr, addrVec);
}

int GetHostIpV4Strings(std::set<std::string> *ipSet)
{
    if (nullptr == ipSet) return -1;

    std::vector<struct ifaddrs> vIfInet4Addrs;
    if (GetIfInet4Addrs(&vIfInet4Addrs) != 0) return -2;

    struct sockaddr_in * vpSockAddr = nullptr;
    char vIpStr[INET_ADDRSTRLEN];
    for (const auto & vIfAddr : vIfInet4Addrs) {
        vpSockAddr = reinterpret_cast<struct sockaddr_in *>(vIfAddr.ifa_addr);
        if (nullptr == inet_ntop(
                    AF_INET,
                    &vpSockAddr->sin_addr.s_addr, // uint32_t
                    vIpStr,
                    INET_ADDRSTRLEN)) {
            return -3;
        }
        ipSet->emplace(vIpStr);
    }

    return 0;
}

int GetHostIpV6Strings(std::set<std::string> *ipSet)
{
    if (nullptr == ipSet) return -1;

    std::vector<struct ifaddrs> vIfInet4Addrs;
    if (GetIfInet6Addrs(&vIfInet4Addrs) != 0) return -2;

    struct sockaddr_in6 * vpSockAddr = nullptr;
    char vIpStr[INET6_ADDRSTRLEN];
    for (const auto & vIfAddr : vIfInet4Addrs) {
        vpSockAddr = reinterpret_cast<struct sockaddr_in6 *>(vIfAddr.ifa_addr);
        if (nullptr == inet_ntop(
                    AF_INET6,
                    &vpSockAddr->sin6_addr.s6_addr, // uint8_t[16]
                    vIpStr,
                    INET6_ADDRSTRLEN)) {
            return -3;
        }
        ipSet->emplace(vIpStr);
    }

    return 0;
}

int GetNonLoopbackHostIpStrings(std::set<std::string> *ipSet, bool needV4)
{
    int vRc = needV4 ? GetHostIpV4Strings(ipSet) : GetHostIpV6Strings(ipSet);
    if (vRc < 0) return -1;

    std::set<std::string> vNonLoopbacks;
    for (const auto & vIp : *ipSet) {
        if (!IsLoopbackIp(vIp)) {
            vNonLoopbacks.emplace(vIp);
        }
    }
    ipSet->swap(vNonLoopbacks);

    return 0;
}

int GetNonLoopbackHostIpV4Strings(std::set<std::string> *ipSet)
{
    return GetNonLoopbackHostIpStrings(ipSet, true);
}

int GetNonLoopbackHostIpV6Strings(std::set<std::string> *ipSet)
{
    return GetNonLoopbackHostIpStrings(ipSet, false);
}

int GetNonLoopbackHostIpStrings(std::set<std::string> *ipSet)
{
    return GetHostIpStrings(ipSet, false);
}

TEST(TSNetwork, GetLocalIpTest)
{
    std::set<std::string> vIpSet;
    EXPECT_EQ(0, GetHostIpStrings(&vIpSet));
    std::cout << "Host Ips: " << std::endl;
    for (const auto & ip : vIpSet) {
        std::cout << ip << std::endl;
    }

    vIpSet.clear();
    EXPECT_EQ(0, GetNonLoopbackHostIpStrings(&vIpSet));
    std::cout << "Non-loopback host Ips: " << std::endl;
    for (const auto & ip : vIpSet) {
        std::cout << ip << std::endl;
    }

    vIpSet.clear();
    EXPECT_EQ(0, GetHostIpV4Strings(&vIpSet));
    std::cout << "Local V4 Ips: " << std::endl;
    for (const auto & ip : vIpSet) {
        std::cout << ip << std::endl;
    }

    vIpSet.clear();
    EXPECT_EQ(0, GetHostIpV6Strings(&vIpSet));
    std::cout << "Local V6 Ips: " << std::endl;
    for (const auto & ip : vIpSet) {
        std::cout << ip << std::endl;
    }

    vIpSet.clear();
    EXPECT_EQ(0, GetNonLoopbackHostIpV4Strings(&vIpSet));
    std::cout << "Non-loopback host v4 Ips: " << std::endl;
    for (const auto & ip : vIpSet) {
        std::cout << ip << std::endl;
    }
}
