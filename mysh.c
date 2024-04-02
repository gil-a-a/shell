#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define TERMINAL_BUFFER_SIZE 4080

void help()
{
    printf("MySh_v.1.0\n");
    printf("Digite o comando e em seguida seus argumentos (Se necessário) para executá-lo\n");
    printf("Formato: [comando] [arg1] [arg2] ... [argN]\n\n");
    printf("Exemplos:\n\tls -a .\n\tvim teste.c\n\tmkdir dir_name\n\t7z x file.zip\n");
}

void execute_command(char *command)
{
    if (!strcmp("help", command)){
        help();
        return;
    }

    printf("pid: %d\n", getpid());
    execvp(command, NULL);
}

int main ()
{
	char *p, command[TERMINAL_BUFFER_SIZE];

	while(1){
        printf("[MySh]$ ");
		fgets(command, TERMINAL_BUFFER_SIZE, stdin);
        if ((p = strchr(command, '\n')) != NULL) *p = '\0';
		printf("Comando: %s\n", command);

		if (!strcmp("exit", command)){
            printf("\n");
            break;
		}

        pid_t pid = fork();
        if (pid == 0){
            execute_command(command);
            return 0;
        } else if (pid < 0)
            exit(1);
	}

	return 0;
}
