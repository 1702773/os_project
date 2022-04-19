#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int normalexec(char userinput[10][1024]){
    //printf("normalexectest start-----------------\n");
    /*for(int i = 0 ; i < 4;i++){
        printf("Your %d input is:%s\n",i,userinput[i]);
    }*/
    //printf("Your input is :%s\n",userinput[0]);
    uid_t child;
    char * userpath = "";
    for(int i = 0 ; i < 10;i++){
        if(strcmp(userinput[0],"cd")==0){
            //char uspwd[256];
            //printf("cd功能\n");
            //printf("your cd input is:%s\n",userinput[1]);
            if(strcmp(userinput[1],"")==0){
                //printf("請輸入您要進入哪個資料夾\n");
            }else{
                //printf("cd start------------\n");
                chdir(userinput[1]);
                //printf("cd end--------------\n");

            }
            break;
        }else if(strcmp(userinput[0],"pwd")==0){
            //printf("pwd功能\n");
            child=fork();
            if(child==0){
                execl("/bin/pwd","pwd",NULL);
            }else{
                wait(0);
                break;
            }
            break;
        }else if(strcmp(userinput[0],"ls")==0){
            //printf("ls功能\n");
            child=fork();
            if(child==0){
                if(strcmp(userinput[1],"-la")==0){
                    execl("/bin/ls","ls","-la",NULL);
                }else if(strcmp(userinput[1],"-l")==0){
                    execl("/bin/ls","ls","-l",NULL);    
                }else if(strcmp(userinput[1],"-a")==0){
                    execl("/bin/ls","ls","-a",NULL);    
                }else{
                    execl("/bin/ls","ls",NULL);
                }
            }else{
                wait(0);
                break;
            } 
            break;
        }else{
            printf("功能尚未齊全\n");
            break;
        }
    }
    //printf("normalexectest end-----------------\n");
    return 0;
}