#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

void cd_change_pwd () {

}

void cd_home () {

}

void cd_less () {

}

int cd (t_stin_content *content) {
	char *tmp = getenv_value("PWD");

	printf("%s << PWD\n", tmp);
	
	int i = modify_env_value("PWD", "TEST");

	printf("%d << i\n", i);
	return (1);
}