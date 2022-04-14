#include <stdio.h>
int pipetest(char userinput[4][1024]){
    printf("pipetest start-----------------\n");
        for(int i = 0 ; i < 4;i++){
        printf("Your %d input is:%s\n",i,userinput[i]);
    }
    printf("pipetest start-----------------\n");
    return 0;
}