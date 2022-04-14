#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/*
內建 shell 命令的函式宣告：
 */
int lsh_cdy(char **args);
int lsh_helpy(char **args);
int lsh_exity(char **args);
int lsh_pwdy(char **args);
int lsh_lsy(char **args);
/*
內建命令列表，以及它們對應的函式。
 */
char *builtin_str[] = {
    "cdy",
    "helpy",
    "exity",
    "pwdy",
    "lsy",
};

int (*builtin_func[]) (char **) = {
    &lsh_cdy,
    &lsh_helpy,
    &lsh_exity,
    &lsh_pwdy,
    &lsh_lsy
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/*
內建命令的函式實現。
*/
int lsh_pwdy(char **args){
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL){
        fprintf(stdout, "%s\n", cwd);
    }
    else {
        printf("getcwd() error!\n");
    }

    return 1;
}

int lsh_lsy(char **args){

    int child = fork();
    if(child == 0){
        if(args[1]==NULL){
            execl("/bin/ls","ls",NULL);
        }else{
            execl("/bin/ls","ls","-la",NULL);
        }
    }
    else{
        wait(0);
    }

    return 1;

}

int lsh_cdy(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "You may need to enter \"cd\" to something!\n");
} else {
    if (chdir(args[1]) != 0) {
        printf("Your enter is error!\n");
}
}
return 1;
}

int lsh_helpy(char **args)
{
    int i,j=0;
    printf("\n");
    printf("Welcome to the helpy!\n");
    printf("The following instructions you can use.\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

for (i = 0; i < lsh_num_builtins(); i++) {

    printf("%d: %s\n",i+1, builtin_str[i]);
}
    printf("\n");
    printf("\n");
    return 1;
}

int lsh_exity(char **args)
{
    return 0;
}

int lsh_execute(char **args)
{
    int i;

    if (args[0] == NULL) {
    // 使用者輸入了一個空命令
    return 1;
    }

for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
    return (*builtin_func[i])(args);
    }
}

return lsh_launch(args);
}

char **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

    if (position >= bufsize) {
        bufsize += LSH_TOK_BUFSIZE;
        tokens = realloc(tokens, bufsize * sizeof(char*));
    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
}

    token = strtok(NULL, LSH_TOK_DELIM);
}
    tokens[position] = NULL;
    return tokens;
}

char *lsh_read_line(void){
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // 讀一個字元
        c = getchar();

        // 如果我們到達了 EOF, 就將其替換為 '\0' 並返回。
    if (c == EOF || c == '\n') {
        buffer[position] = '\0';
        return buffer;
    } else {
        buffer[position] = c;
    }
    position++;

    // 如果我們超出了 buffer 的大小，則重新分配。
    if (position >= bufsize) {
        bufsize += LSH_RL_BUFSIZE;
        buffer = realloc(buffer, bufsize);
    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
        }
    }
    }
}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do {
        printf(">> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
        } while (status);
}

int lsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
    // 子程序
    if (execvp(args[0], args) == -1) {
        printf("Your enter is error!\n");
    }
    exit(EXIT_FAILURE);
    } else if (pid < 0) {
    // Fork 出錯
        printf("Your enter is error!\n");
    } else {
    // 父程序
    do {
    wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
    }



int main(int argc, char **argv)
{
    // 如果有配置檔案，則載入。

    // 執行命令迴圈
    lsh_loop();

    // 做一些關閉和清理工作。

    return EXIT_SUCCESS;
}

