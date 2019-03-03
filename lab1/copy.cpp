#include<iostream>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<fcntl.h>
#include<sys/syscall.h>
using namespace std;
const int SIZE = 100;
int main(int argc, const char *argv[])
{
    int src, dst;   //文件描述符
    int len;
    char buf[SIZE];
    try
    {
        if( argc > 2 ) {
            src = open(argv[1],O_RDONLY);
            if( src < 0 )
                throw runtime_error("Fail to open "+string(argv[1]));
            dst = open(argv[2], O_WRONLY|O_CREAT, 0666);
            if( dst < 0 )
                throw runtime_error("Fail to open "+string(argv[2]));
        }
        else 
            throw runtime_error("arguments are less than 3");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }
    while( ( len = read(src, buf, SIZE) ) > 0 ) {
        write(dst, buf, len);
    }
    close(src);
    close(dst);
    return 0;
}