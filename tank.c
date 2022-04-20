#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "tankfunction.h"
int main(int argc ,char * argv[]){
int type = 1 ;
char userpwd[1024];
realpath(argv[0],userpwd);
printf("\033[;36m");
printf("If you didn`t know What are you want\nYou can type help\n");
while(type!=0){
    char usertype[1024];
    printf("\033[;31m");//設定顏色紅色
    printf("TankBash/.>");  
    printf("\033[0;34m");//設定之後的顏色為藍色
    fgets(usertype,256,stdin);

    //printf("%s\n",usertype);
    //將輸入的字串進行分割
    if(usertype[strlen(usertype)-1]=='\n'){
        usertype[strlen(usertype)-1]='\0';
    }
    usertype[strlen(usertype)]= ' ';
    int spacecount = 0 ;
    for(int i = 0 ; i < strlen(usertype);i++){
        if(usertype[i]==' '){
            spacecount++;
        }
    }
    //printf("%s\n",usertype[0]);
    //printf("Your input numbers %lu\n",strlen(usertype));
    //設定可以在後面接受argv概念的陣列，上限為3個

    //printf("spacecount: %d\n",spacecount);
    //printf("%s\n",typeid(spacecount).name());

    char userinput[10][1024]={' '};
    //userinput[spacecount][1024]={' '};
    //char userinput[4][1024]={' '};
    //userinput="Hnkaaaaaa";
    spacecount = 0 ;
    int testa = 0;
    for(int i = 0 ; i < strlen(usertype);i++){
        if(usertype[i]==' '){
            //printf("%s\n",userinput[spacecount]);
            strncpy(userinput[spacecount],&usertype[testa],i-testa);
            spacecount++;
            testa=i+1;
        }   
    }
    //printf("總共有%d個空白\n",spacecount);
    if(spacecount>10){
        printf("您的輸入過多，最多只能輸入10個\n");
        exit(1);
    }
    /*for(int i = 0 ; i < 4;i++){
        printf("Your %d input is:%s\n",i,userinput[i]);
    }*/
    int type = 0 ;
    //type 1 為 io , 2 為 pipe , 3 為 一般模式 
    for(int i = 0 ; i < 10;i++){
        //printf("%d\n",type);
        if(strcmp(userinput[0],"exit")==0){
            printf("Bye\n");
            exit(3);
        }else if((strcmp(userinput[i],">>")==0)||(strcmp(userinput[i],"<<")==0)){
            type = 1;
            break;
        }else if(strcmp(userinput[i],"||")==0){
            type = 2 ;
            break;
        }else{
            type =3;
        }
    }
    if(type==1){
        iotest(userinput);
        continue;
    }else if (type==2){
        pipetest(userinput);
        //printf("pipetest finish\n");
        continue;
    }else if (type==3){
        normalexec(userinput);
        continue;
    }else{
        printf("找不到型態");
        exit(1);
    }
}
}