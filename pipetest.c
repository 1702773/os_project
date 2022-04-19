#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "tankfunction.h"

int pipetest(char userinput[4][1024]){
    //printf("pipetest start-----------------\n");
        for(int i = 0 ; i < 4;i++){
        printf("Your %d input is:%s\n",i,userinput[i]);
        if(strcmp(userinput[i],"||")==0){
            printf("偵測到pipe符號\n");
            //pipe為將前面執行出來的結果丟到後面
            //例如：history | grep "make"
            //將history輸出 導入到 grep的輸入中 並利用grep取出含有make的輸出
            //所以左邊要先做輸出導入到右邊
            //先以將上面這行程式碼可以執行為目標
            pid_t child ;
            int p[2];
            int i ;
            pipe(p);
            child = fork();
            if(child==0){
                close(1);
                dup(p[1]);
                write(p[1],"This is child process\n",50);
                exit(0);
                //close(1);
                //close(1);
                //write(p[1],"this is test\n",25);
                //system("ls");
                //system("pwd");
                //system("ls -la");
                //printf("%d\n",system("history"));
            }else{
                close(0);
                dup(p[0]);
                char buf[1024];
                read(p[0],buf,sizeof(buf));
                printf("%s\n",buf);
                //char buf[1024];
                //read(p[0],buf,sizeof(buf));
                //printf("%s\n",buf);
                //printf("grep test\n");
                //int fd = open("./pipecount.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
                //write(fd,buf,sizeof(buf));
                //int a = execl("/usr/bin/grep",NULL);
                //printf("%d\n",a);
                printf("grep test finish\n");
                break;
                
            }
            
        }
    }
    //printf("pipetest start-----------------\n");
    return 0;
}