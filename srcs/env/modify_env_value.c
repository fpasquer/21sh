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
		if (curs->name && ft_strcmp(name, curs->name) == 0) {
			ft_memdel((void**)&(curs->value));
			if ((curs->value = ft_strdup(value)) == NULL)
				return (false);
			return (true);
		}
		curs = curs->next;
	}
	return (false);
}