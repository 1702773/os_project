#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char *argv[]){
    int p[2],status,done=0;
    pipe(p);
    pid_t child;

    child = fork();

    if(child==0){
        dup2(p[1],1);
        execlp(argv[1],argv[1],(char * )NULL);
    }
    child = fork();
    if(child==0){
        close(p[1]);
        dup2(p[0],0);
        execlp(argv[2],argv[2],(char * )NULL);
    }
    close(p[0]);
    close(p[1]);

    //waitpid(-1,&status,0);
    //waitpid(-1,&status,0);
    printf("%s\n%s\n",argv[1],argv[2]);

}