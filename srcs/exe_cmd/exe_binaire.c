#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

/*
** FONCTION TEMPORAIRE DE PACOURS TABLE DE HASH MDR KOOQKWEEF LOL
*/
char 		*cekoicebordel(char *bin_to_find) {
	t_21sh *sh;
	t_bin *tmp;

	if ((sh = get_21sh(NULL)) == NULL)
		return (NULL);
	int index = 0;
	while (index < SIZE_HASH)
	{
		tmp = sh->hash[index];
		while (tmp) {
			if (ft_strequ(tmp->name, bin_to_find))
				return (tmp->path_name);
			tmp = tmp->next;
		}
		index++;
	}
	return (NULL);
}


int 		exe_binaire(t_cmd *cmd, char **env) {

	char *path = cekoicebordel(cmd->arg[0]);

	int pid = fork();
	if (pid == 0) {
		if (execve((path) ? path : ".", cmd->arg, env) == -1) {
			exit (-1);
		}
	} else {
		wait(NULL);
	}
	return (true);
}