#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							modify_env_value(char *name, char *value)
{
	t_env					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (false);
	curs = sh->env;
	while (curs != NULL)
	{
		if (ft_strcmp(name, curs->name) == 0) {
			free(curs->name);
			curs->name = ft_strdup(value);
			return (true);
		}
		curs = curs->next;
	}
	return (false);
}