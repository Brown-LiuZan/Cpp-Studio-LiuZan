#include <sstream> //std::stringstream
#include <iostream>
#include <string>
#include <string.h> //strerror()
#include <unistd.h> //TEMP_FAILURE_RETRY
#include <errno.h> //EINTR
#include <stdio.h> 
#include <fcntl.h> //O_TRUNC, O_SYNC, O_RDWR
#include <sys/stat.h> //S_IRWXU
#include <sys/types.h>
#include <sys/ioctl.h> //ioctl()
#include <sys/mount.h> //BLKSSZGET

int main()
{
#if 0
    int vFd = open("UsageOfDevSecSizeGet.txt", O_TRUNC | O_SYNC | O_RDWR | O_CREAT, S_IRWXU);
#else
    int vFd = open("/dev/xvda1", O_RDWR);
#endif
    if (vFd < 0) {
        std::cerr << "Failed to open file:[" << errno << "] " << strerror(errno) << std::endl;
        if (EACCES == errno) std::cerr << "Please run it as the root user." << std::endl;
        return -1;
    } else {
        std::cout << "Succeeded to open file" << std::endl;
    }

    int vSectorSize = 0;
    int vRc = ioctl(vFd, BLKSSZGET, &vSectorSize);
    if (vRc < 0) {
        std::cerr << "Failed to get the sector size of device:[" << errno << "] " << strerror(errno) << std::endl;
        goto CLEANUP;
    } else {
        std::cout << "The device sector size: " << vSectorSize << " bytes." << std::endl;
#if 0
        std::stringstream vStrStream;
        vStrStream << "Device sector size of this file: " << vSectorSize << std::endl;
        int vBytesWritten = TEMP_FAILURE_RETRY(write(vFd, vStrStream.str().c_str(), vStrStream.str().size()));
        if (vBytesWritten < 0) {
            std::cerr << "Failed to write file." << std::endl;
            vRc = -1;
        }
#endif
    }

    CLEANUP:
    vFd = close(vFd);
    if (vFd != 0) {
        std::cerr << "Failed to close file." << std::endl;
        vRc = -1;
    } else {
        std::cout << "Succeeded to close file." << std::endl;
    }

    return vRc;
}
