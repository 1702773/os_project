#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "tankfunction.h"
int iotest(char userinput[10][1024]){
    printf("iotest start-----------------\n");
        for(int i = 0 ; i < 10;i++){
        printf("Your %d input is:%s\n",i,userinput[i]);
    }
    //先判斷是輸入還是輸出,先以可以讓ls輸出到一個txt檔案為目標
    for(int i = 0 ; i < 10;i++){
        pid_t child;
    if(strcmp(userinput[i],"<<")==0){
        printf("input\n");
        char ioinput[10][1024] = {' '};
        //userinput[i]之後的為檔案名稱 
        
        char iofile[1024] = {' '};
        strcpy(iofile,userinput[i+1]);
        //userinput[i]之前為指令
        if(strcmp(userinput[i-1],"")==0){
            printf("Please reinput\n");
            break;
        }else{
            if(strcmp(userinput[i+1],"")==0){
                printf("Please input what file do you want input\n");
                break;               
            }else{
                for(int k = 0;k<i;k++){
                    strcpy(ioinput[k],userinput[k]);
                    printf("ioinput array %d is:%s\n",k,ioinput[k]);
                }
            }
            int fd = open(iofile,O_RDONLY,S_IRUSR|S_IWUSR);
            printf("The fd is :%d\n",fd);
            if(fd==-1){
                printf("Your input file name not exist Please reinput\n");
                break;
            }else{
                char temp[1024];
                //printf("open read only test\n");
                //read file test1.txt to printf
                read(fd,temp,1024);
                printf("The file content is :%s\n",temp);
                strcpy(ioinput[i],temp);
                for(int k = 0;k<=i;k++){
                    if(k==i){
                        strcpy(ioinput[k],temp);
                        //printf("ioinput array %d is:%s\n",k,ioinput[k]);
                    }else{
                        strcpy(ioinput[k],userinput[k]);
                        //printf("ioinput array %d is:%s\n",k,ioinput[k]);
                    }
                }
                normalexec(ioinput);
            }
            //normalexec(ioinput);
            //userinput[i]之前的為指令
            //normalexec(userinput);
            //int fd =open("/dev/tty",O_WRONLY);
            //stdout = fdopen(fd,"w");
        }
        //將檔案內容導入到指令
        break;
    }else if(strcmp(userinput[i],">>")==0){
        printf("output\n");
        printf("ls output test\n");
        char ioinput[4][1024] = {' '};
        //userinput[i]之後的為檔案名稱 
        char iofile[1024] = {' '};
        strcpy(iofile,userinput[i+1]);
        //printf("%s\n",userinput[i+1]);
        if(strcmp(userinput[i+1],"")==0){
            printf("Please input what file you want input\n");
            break;
        }else{
            for(int k = 0;k<i;k++){
                strcpy(ioinput[k],userinput[k]);
                printf("ioinput array %d is:%s\n",k,ioinput[k]);
            }
            close(1);
            open(iofile,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
            //printf("This is a test\n");
            normalexec(ioinput);
            //userinput[i]之前的為指令
            //normalexec(userinput);
            int fd =open("/dev/tty",O_WRONLY);
            stdout = fdopen(fd,"w");
        }
        //open("./output.txt", O_RDWR | O_CREAT ,S_IRUSR | S_IWUSR);
        //dup(1);   
        printf("io output finish\n");
        break;
    }else{
        
    }
    printf("iotest end-----------------\n");
    }
    return 0;

}
