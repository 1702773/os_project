#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
int main(){


pid_t pid;
pid = fork();

if(pid==0){
	printf("This is Child Process---\n");
	//execl("/bin/ls","ls","-l",NULL);
	//char * envp[] = {"AA=11","BB=22",NULL};
	//execle("/bin/ls","ls",NULL,envp);
	//execlp("ls","ls","-l",NULL);
	char * argv[] = {"ls","-l",NULL};
	//execv("/bin/ls",argv);
	//execvp("ls",argv);
	execvpe("ls",argv);
}else if (pid > 0){
	wait(0);
	printf("This ia Parent Process---\n");
}else{
 printf("Error!\n");
}
return 0; 
}
