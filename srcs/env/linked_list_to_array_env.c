#include "../incs/shell_21sh.h"
#include "../incs/key.h"

/*
** DEBUG TEMPORAIRE PRINT
*/

void 				ft_print_env_array(char **env)
{
	int 			i;

	i = 0;
	while (env[i]) {
		ft_putendl(env[i]);
		i++;
	}
}

/*
**
*/

char				**l_l_to_arr_env() {
	t_21sh 			*sh;
	t_env 			*env;
	char 			**new_env;
	int 			i;

	i = 0;
	if ((sh = get_21sh(NULL)) == NULL)
		return (NULL);
	env = sh->env;
	if ((new_env = ft_memalloc(sizeof(char*) * (sh->nb_var_env + 1))) == NULL)
		return (NULL);
	while (env) {
		if ((new_env[i] = ft_multijoin(3, env->name, "=", env->value)) == NULL)
			break ;
		env = env->next;
		i++;
	}
	new_env[i] = NULL;
	// ft_print_env_array(new_env);
	return (new_env);
}

int 				delete_env_array(char **env) {
	int 			i;

	i = 0;
	if (!env) {
		return (false);
	}
	while (env[i]) {
		free(env[i]);
		i++;
	}
	free(env);
	return (true);
}