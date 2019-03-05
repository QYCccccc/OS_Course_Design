#include<unistd.h>
#include<syscall.h>

int main()
{
    syscall(520, "sys.c", "dst.txt");
    return 0;
}