#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int main(){


pid_t pid;
pid = fork();

if(pid==0){
 printf("Child process!\n");
 close(1);
 open("./q2.txt" , O_CREAT|O_WRONLY,S_IWUSR);
 printf("This is child print to txt test!!\n");
 
}else if (pid > 0){
 printf("Parent process!\n");
 //wait(0);
 close(1);
 open("./q2.txt" , O_CREAT|O_WRONLY,S_IWUSR);
 printf("This is parent print to txt test!!\n");
}else{
 printf("Error!\n");
}
return 0; 
}
