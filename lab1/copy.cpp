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
        if( argc > 2 ) {    //当命令合法时
            src = open(argv[1],O_RDONLY);   //打开源文件
            if( src < 0 )   //打开失败则抛出异常
                throw runtime_error("Fail to open "+string(argv[1]));
            dst = open(argv[2], O_WRONLY|O_CREAT, 0666);    //打开目标文件
            if( dst < 0 )   //打开失败则抛出异常
                throw runtime_error("Fail to open "+string(argv[2]));
        }
        else    //命令非法时抛出异常
            throw runtime_error("arguments are less than 3");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1); //发生异常时，退出
    }
    //实现文件拷贝
    while( ( len = read(src, buf, SIZE) ) > 0 ) {
        write(dst, buf, len);
    }
    close(src);
    close(dst);
    return 0;
}