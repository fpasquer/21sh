#include "21sh.h"

int main(int argc, char **argv, char **env)
{
	int pid = 0;

	if (argc > 1) {
		pid = fork();
		if (pid < 0) {
			perror("ERROR FORK");
		}
		else if (pid != 0) {
			printf("parent\n");
			wait(NULL);
		}
		else {
			printf("child\n");
			int fd = open("test.txt", O_WRONLY);
			int test = dup2(fd, 2);
			//printf("%d = test, %d = fd\n", test, fd);
			//close(0);
			execve("/bin/ls", &argv[1], env);
		}
	}
	return (0);
}
