#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
int main(){
pid_t pid,pid1;
int p[2];
int i ;
pipe(p);
pid = fork();
if(pid==0){
	pid1 = fork();
	if(pid1==0){
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
	  	execl("/bin/wc","wc",NULL);	

	}else{
		close(p[0]);
		write(p[1],"Temi test\n",12);
		close(p[1]);
	}
	
}else{
	
	int a = wait(0);
	printf("This wait is :%d\n",a);
	
}
return 0; 
}
