#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;
int main()
{
    pid_t p1, p2, p3;
    if((p1 = fork()) == 0) {
        //子进程1
        cout<<"clock process was created!\n";
        execvp("./lab1_2", NULL);
    }
    else {
        //父进程
        if((p2 = fork()) == 0) {
            //子进程2
            cout<<"cycle display numbers process was created!\n";
            execvp("./lab1_3", NULL);
        }
        else {
            //父进程
            if((p3 = fork()) == 0) {
                //子进程3
                cout<<"sum process was created!\n";
                execvp("./lab1_4", NULL);
            }
            else {
                //父进程
                cout<<"waiting process finish!\n";
                waitpid(p1, NULL, 0);
                waitpid(p2, NULL, 0);
                waitpid(p3, NULL, 0);
                cout<<"Finished!\n";
                return 0;
            }
        }
    }
}