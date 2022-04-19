#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "tankfunction.h"

int pipetest(char userinput[10][1024]){
    //printf("pipetest start-----------------\n");
        for(int i = 0 ; i < 10;i++){
        printf("Your %d input is:%s\n",i,userinput[i]);
        if(strcmp(userinput[i],"||")==0){
            printf("偵測到pipe符號\n");
            //pipe為將前面執行出來的結果丟到後面
            //例如：ls -la | sort -r 
            //將ls -la 輸出 導入到 sort的輸入中 
            //所以左邊要先做輸出導入到右邊
            //先以將上面這行程式碼可以執行為目標
            pid_t child ;
            int p[2];
            int a,k ;
            pipe(p);
            child = fork();
            if(child==0){
                //將pipe前面的結果導入到p[1]
                dup(p[1]);
                close(1);
                printf("%d\n",i);
                char abuf[10][1024]={' '};
                for(k = 0;k<i;k++){
                    strcpy(abuf[k],userinput[k]);
                }
                for(k=0; k <i;k++){
                    
                    printf("%s\n",abuf[k]);
                }
                int fd =open("/dev/tty",O_WRONLY);
                stdout = fdopen(fd,"w");
                normalexec(abuf);
                //write(p[1],"This is child process\n",50);
                //exit(0);
            }else{
                //close(0);
                //close(0)會造成系統問提，如關有關必須要額外再打開
                dup(p[0]);
                char *buf[1024];
                printf("This is parent process to use child data\n");
                read(p[0],buf,sizeof(buf));
                wait(0);
                printf("Finish\n");
                execvp(userinput[i+1],buf);
                //char buf[1024];
                //read(p[0],buf,sizeof(buf));
                //printf("%s\n",buf);
                //printf("grep test\n");
                //int fd = open("./pipecount.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
                //write(fd,buf,sizeof(buf));
                //int a = execl("/usr/bin/grep",NULL);
                //printf("%d\n",a);
                //int fd =open("/dev/tty",O_WRONLY);
                //stdin = fdopen(fd,"w");
                break;
                
            }
            break;
        }
    }
    //printf("pipetest start-----------------\n");
    return 0;
}