#include "21sh.h"

int main(int argc, char **argv, char **env)
{
	int pid = fork();
	if (pid < 0) {
		perror("ERROR FORK");
	}
	else if (pid != 0) {
		printf("parent\n");
		wait(NULL);
	}
	else {
		printf("child\n");
	}
	printf("%d\n", pid);
	return (0);
}
