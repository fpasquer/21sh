#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static void 		del_env_(t_env **env) 
{
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = NULL;
}

int 		builtin_unsetenv(t_cmd *content) {
	t_21sh	*sh;
	t_env	*env = NULL;
	t_env	*env_next = NULL;

	if (content->argc == 1 || (content->argc > 1 && ft_strchr(content->arg[1], '='))) {
		ft_putendl("The name argument is a null pointer, points to an empty string, or points to a string containing an '=' character.");
	} 
	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	env = sh->env;
	if (content->argc > 1)
		env_next = sh->env->next;
	if (ft_strequ(env->name, content->arg[1])) {
		del_env_(&env);
		sh->env = env->next;
		sh->nb_var_env--;
	}
	else {
		while (env_next) {
			if (ft_strequ(env_next->name, content->arg[1])) {
				env->next = env_next->next;
				del_env_(&env_next);
				sh->nb_var_env--;
				break ;
			}
			env = env->next;
			env_next = env_next->next;
		}
	}
	return (true);
}