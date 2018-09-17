#include<sys/mman.h>
#include<sys/stat.h>

class BufferedInputStream {
    private: char *buf, *p;
    private: int size;
    public: BufferedInputStream()
    {
        int fd=fileno(stdin);
        struct stat sb;
        fstat(fd,&sb);
        size=sb.st_size;
        buf=reinterpret_cast<char *>(mmap(0,size,PROT_READ,MAP_PRIVATE,fileno(stdin),0));
        p=buf;
    }
    public: inline char nextChar(){
        return (p == buf + size || *p == -1) ? -1 : *p++;
    }
}ReadStream;