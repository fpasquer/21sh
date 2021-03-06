#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

int 		builtin_setenv(t_cmd *content) {
	t_21sh  *sh;
	char 	*env_name;
	char 	*env_value;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (content->argc == 1) {
		ft_putendl("Error: the name argument is a null pointer, or points to an empty string");
		return (false);
	}
	if (content->argc > 1) {
		if (ft_strchr(content->arg[1], '=') || ft_strequ("", content->arg[1])) {
			ft_putendl("Error: the name argument points to a string containing an '=' character.");
			return (false);
		}
		env_name = content->argc > 1 ? content->arg[1] : NULL;
		env_value = content->argc > 2 ? content->arg[2] : ft_strdup("");
		if (check_if_env_exist(env_name) == false) {
			add_env_(env_name, env_value);
		}
		else {
			modify_env_value(env_name, env_value);
		}
		if (ft_strequ(env_name, "PATH")) { 

			/*
			** TMP;
			*/
			ft_putendl("OK");
			del_bin();
			//char *str = ft_multijoin(3, env_name,"=" , env_value);
			ft_putendl(env_value);
			printf("%d\n", save_path(&sh, env_value));
			ft_putendl("OK");
			// free(str);
		}
	}
	return (true);
}