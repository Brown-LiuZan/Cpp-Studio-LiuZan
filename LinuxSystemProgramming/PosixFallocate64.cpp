#include <iostream>                                                                 
#include <iomanip>                                                                  
#include <unistd.h>                                                                 
#include <fcntl.h>                                                                  
#include <sys/types.h>                                                              
#include <sys/stat.h>                                                               
#include <sys/syscall.h>                                                               
#include <string.h>                                                                 
#include <errno.h>                                                                  
#include <cassert>                                                                  
                                                                                    
using namespace std;                                                                
                                                                                    
int main()                                                                          
{                                                                                   
    assert(sizeof(off_t) == sizeof(off64_t));                                       
                                                                                    
    const int SECTOR_SIZE = 4096;                                                   
#if 0
    int vOpenFlag = O_CREAT | O_TRUNC | O_RDWR | O_SYNC;                            
#else
    int vOpenFlag = O_CREAT | O_TRUNC | O_RDWR | O_SYNC | O_DIRECT;               
#endif
    int vFd = open("posix-fallocate-test.txt", vOpenFlag, S_IRUSR | S_IWUSR);       
    if (-1 == vFd)                                                                  
    {                                                                               
        cerr << "Failed to open file." << endl;                                     
    }                                                                               
                                                                                    
    char * vBuf = 0;                                                                
    assert(posix_memalign((void **)&vBuf, SECTOR_SIZE, SECTOR_SIZE) == 0);          
    sprintf(vBuf, "%s",                                                             
        "Hi, posix_fallocate().\n"                                                  
        "You're not nice in direct IO mode.");                                      
    cout << vBuf << endl;                                                           
                                                                                    
    ssize_t vBytesWritten = pwrite(vFd, vBuf, SECTOR_SIZE, 0);                      
    if (-1 == vBytesWritten)                                                        
    {                                                                               
        cerr << "Failed to write file: " << strerror(errno) << endl;                
    }                                                                               
    else                                                                            
    {                                                                               
        cout << "Bytes written: " << vBytesWritten << endl;                         
    }                                                                               
                                                                                    
#if 0
    //int vRc = syscall(SYS_fallocate, vFd, 0, SECTOR_SIZE, 0x100000);
    int vRc = syscall(SYS_fallocate, vFd, 0, 256, 0x100000);
#else
    //int vRc = posix_fallocate(vFd, SECTOR_SIZE, 0x100000);                          
    int vRc = posix_fallocate(vFd, 256, 0x100000);                          
#endif
    if (0 != vRc)                                                                   
    {                                                                            
        cerr << "Failed to extend file: " << strerror(vRc) << endl;              
        cerr << "With O_DIRECT, posix_fallocate() always fails with EINV." <<    
            endl;                                                                
    }                                                                            
    else                                                                         
    {                                                                            
        cout << "New offset: 0x" << hex << lseek(vFd, 0, SEEK_END) << endl;      
    }                                                                            
                                                                                 
    close(vFd);                                                                  
                                                                                 
    return 0;                                                                    
}
