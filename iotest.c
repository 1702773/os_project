#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int iotest(char userinput[4][1024]){
    printf("iotest start-----------------\n");
        for(int i = 0 ; i < 4;i++){
        printf("Your %d input is:%s\n",i,userinput[i]);
    }
    //先判斷是輸入還是輸出,先以可以讓ls輸出到一個txt檔案為目標
    if(strcmp(userinput[1],"<<")==0){
        printf("input\n");
    }else if(strcmp(userinput[1],">>")==0){
        printf("output\n");
        printf("ls output test\n");
        close(1);
        open("./output.txt", O_WRONLY | O_CREAT );
        printf("asasdsdsdsdsd");
        fclose(fp);
    }else{
        printf("ioerror\n");
    }
    printf("iotest end-----------------\n"); 
    return 0;

}