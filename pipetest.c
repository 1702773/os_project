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
                //printf("偵測到pipe\n");
                // 左邊將stdout接到p[0]||右邊將stdin接到p[1]
                pid_t child;
                int p[2],status,done=0;
                pipe(p);
                //char pipeinput[10][1024]={' '};
                //printf("%s\n",userinput[0]);
                //printf("%s\n",userinput[2]);
                //printf("i is:%d\n",i);
                child = fork();
                if(child==0){
                       //fflush(stdout);   
                       close(p[0]);
                       dup2(p[1],STDOUT_FILENO);
                       //printf("%d\n",dup2(p[1],1));
                       execlp(userinput[0],userinput[0],NULL);
                       //break;
                       //exit(0);
                       
                }
                child= fork();
                if(child==0){
                        //fflush(stdout);
                        //printf("hello is me\n");
                        close(p[1]);
                        //printf("This userinput[2] :%s\n",userinput[2]);
                        dup2(p[0],STDIN_FILENO); 
                        //printf("Hello is me \n");
                        execlp(userinput[2],userinput[2],NULL);
                        //break
                        
                }
                //wait(0);
                close(p[0]);
                close(p[1]);
                waitpid(-1,&status,0);
                waitpid(-1,&status,0);
                //printf("%s\n%s\n",userinput[0],userinput[2]);
                //exit(1);
                break;
            }
            
    }
    //printf("pipetest start-----------------\n");
    return 0;
}