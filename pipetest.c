#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "tankfunction.h"

int pipetest(char userinput[10][1024]){
    //printf("pipetest start-----------------\n");
        for(int i = 0 ; i < 10;i++){
            if(strcmp(userinput[i],"||")==0){
                printf("偵測到pipe\n");
                // 左邊將stdout接到p[0]||右邊將stdin接到p[1]
                pid_t child;
                int p[2],status,done=0;
                //char pipeinput[10][1024]={' '};
                printf("%s\n",userinput[0]);
                printf("%s\n",userinput[2]);
                child = fork();
                if(child==0){
                       dup2(p[1],1);
                       printf("%d\n",dup2(p[1],1));
                       execlp(userinput[0],userinput[0],NULL);
                       //break;
                }
                child = fork();
                if(child==0){
                        printf("Child1\n"); 
                        close(p[1]);
                        printf("Child2\n"); 
                        dup2(p[0],0);
                       printf("Child3\n"); 
                        execlp(userinput[2],userinput[2],(char *)NULL);
                        //break;
                }
                close(p[0]);
                close(p[1]);
                //int fd1 =open("/dev/tty",O_WRONLY);
                //stdin = fdopen(fd1,"w");
                //int fd2 =open("/dev/tty",O_WRONLY);
                //stdout = fdopen(fd2,"w");
                //open("./pipetest.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
                //printf("THis is test\n");
                waitpid(-1,&status,0);
                waitpid(-1,&status,0);
                //printf("%s\n%s\n",userinput[0],userinput[2]);
                //exit(0);
                break;
            }
    }
    //printf("pipetest start-----------------\n");
    return 0;
}