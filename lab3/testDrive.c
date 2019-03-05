#include <string.h> 
#include <stdio.h> 
#include <fcntl.h> 
 #include<unistd.h>
int main(void) 
{ 
    int fd; 
    char buf[1024]; 
    char get[1024]; 
 
    memset(get, 0, sizeof(get)); 
    memset(buf, 0, sizeof(buf)); 
 
    fd = open("/dev/mydriver", O_RDWR);//打开设备 
    if (fd > 0) {
	printf("please enter a string you want input to mydriver:\n"); 
        while((scanf("%s",get)) != EOF) {
            read(fd, &buf, sizeof(buf)); 
            printf("The message in mydriver now is: %s\n", buf); 
    
            //将输入写入设备 
            write(fd, &get, sizeof(get)); 
            //读出设备的信息并打印 
            read(fd, &buf, sizeof(buf)); 
            printf("The message changed to: %s\n", buf); 
            sleep(1); 
	    printf("please enter a string you want input to mydriver:\n");

        }
    }  
    else { 
        printf("Open mydriver failed!\n"); 
        return -1; 
    } 
 
    close(fd);//释放设备 
 
    return 0; 
} 
