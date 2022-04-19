#include <stdio.h>
#include <unistd.h>
int main(){
int x = 50 ;
pid_t pid;
pid = fork();
if(pid==0){
 printf("Child process!\n");
 printf("The x is a:%d\n",x);
 x=x+20;	
}else if (pid > 0){
 printf("Parent process!\n");
 printf("The x is a:%d\n",x);
 x=x+30;
}else{
 printf("Error!\n");
}
printf("The x is a:%d\n",x);
return 0; 
}
