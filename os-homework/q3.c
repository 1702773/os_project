#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
int main(){


pid_t pid;
pid = fork();

if(pid==0){
	printf("hello\n"); 
}else if (pid > 0){
	sleep(1);
	printf("goodbye\n");

}else{
 printf("Error!\n");
}
return 0; 
}
