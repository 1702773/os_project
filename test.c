#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc,char * argv[]){

    char a[100] ;
    //a = (char*)malloc(sizeof(char)*10);
    //scanf("%s",a);
    int type = 0;
    int count = 0;
    
    char pwd[255];
    if(!getcwd(pwd,255)){
        perror("getcwd");
        return 1;
    }
    int ret ;
    ret =chdir(argv[1]);
    if(ret){
        printf("Please make sure file path\n");
    }
    printf("chdir %s is success!\n",argv[1]);
//再次使用chdir回到pwd儲存的目錄
	ret = chdir(pwd);
	if(ret){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("chdir %s is success！\n",pwd);
    
	return 0;
}