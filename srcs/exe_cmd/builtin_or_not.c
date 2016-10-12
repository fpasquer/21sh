#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

t_builtin_lst g_builtin_lst[] = {
	{"cd", cd},
	{NULL, NULL},
};

void		builtin_or_not(t_stin_content *content) {
	int 	i;

	i = 0;
	while (g_builtin_lst[i].str) {
		if (ft_strequ(content->bin, g_builtin_lst[i].str)) {
			g_builtin_lst[i].p(content);
		}
		i++;
	}
}