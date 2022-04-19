#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
int main(){


pid_t pid;
pid = fork();

if(pid==0){
	printf("This is Child Process %d\n",(int)getpid());
	//wait(0);
	//printf("%d\n",b);
	close(1);
	printf("close stdout printf test\n");
	
}else if (pid > 0){
	wait(0);
	printf("This is Parent Process %d\n",(int)getpid());
	//wait result is parent pid
	//printf("%d\n",a);
	printf("goodbye\n");

}else{
 printf("Error!\n");
}
return 0; 
}
