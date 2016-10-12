#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							check_if_env_exist(char *name)
{
	t_env					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	curs = sh->env;
	while (curs != NULL)
	{
		if (ft_strcmp(name, curs->name) == 0)
		{
			curs->add = false;
			return (true);
		}
		curs = curs->next;
	}
	return (false);
}
