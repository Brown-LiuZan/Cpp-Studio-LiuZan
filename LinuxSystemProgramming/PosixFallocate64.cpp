#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main()
{
    int vFd = open("posix-fallocate-test.txt",
            O_CREAT | O_TRUNC | O_RDWR,
            S_IRWXU);
    if (-1 == vFd) cerr << "Failed to open file." << endl;

    string vStr("Hi, GLIBC.\n");
    int vBytesWritten = write(vFd, vStr.c_str(), vStr.size());
    if (-1 == vBytesWritten) cerr << "Failed to write file." << endl;

    int vRc = posix_fallocate64(vFd, vStr.size(), 0x100000);
    if (0 != vRc) cerr << "Failed to extend file." << endl;

    close(vFd);

    return 0;
}
