#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int add_env_(char *name, char *value) {
	t_21sh *sh;
	t_env *env;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);	
	env = sh->env;
	if (env) {
		while (env->next) {
			env = env->next;
		}
		if (((env->next = ft_memalloc(sizeof(t_env))) == NULL)) {
			return (ERROR);
		}
		env = env->next;
	}
	else if (((env = ft_memalloc(sizeof(t_env))) == NULL)) {
		return (ERROR);
	}
	sh->nb_var_env++;
	env->name = ft_strdup(name);
	env->value = (value) ? ft_strdup(value) : ft_strdup("");
	env->add = true;
	env->index = sh->nb_var_env;
	return (true);
}