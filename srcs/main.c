#include "21sh.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv, char **env)
{
	int pid = fork();

	if (argc > 1) {
		if (pid < 0) {
			perror("error");
			exit (-1);
		}
		if (pid == 0) {
			printf("child\n");	
			int fw = open("test.txt", O_WRONLY);
			dup2(fw, 1);
			execve("/bin/ls", &argv[1], env);
		}
		else {
			printf("parent\n");
			wait(NULL);
		}
	}
	printf("%d\n", pid);
	return (0);
}
