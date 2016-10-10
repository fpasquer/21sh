/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 09:30:35 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/10 14:34:58 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
# define FLAG_I 1
# define FLAG_P 2
# define FLAG_S 4
# define FLAG_U 8
# define FLAG_V 16

# define OPT_WRONG -2
# define PARAM -3

#include <stdio.h>

static int					change_flag(char *flags, char **l_cmd)
{
	char					*tmp_line;
	bool					option;

	if (flags == NULL || l_cmd == NULL)
		return (ERROR);
	while ((*(*l_cmd)) == '-' || (*(*l_cmd)) == ' ')
	{
		if ((*(*l_cmd)) == '-')
		{
			tmp_line = ++l_cmd[0];
			while (!(option = false) && (*tmp_line == 'i' || *tmp_line == 'u'))
			{
				option = true;
				*flags = (*tmp_line == 'i') ? *flags | FLAG_I : *flags;
				*flags = (*tmp_line++ == 'u') ? *flags | FLAG_U : *flags;
				l_cmd[0]++;
			}
			if (option == false && (*(*l_cmd)) != ' ')
				return (false);
		}
		l_cmd[0]++;
	}
	return (true);
}

static char					get_flags_env(char  **l_cmd)
{
	char					flags;
	char					c_prev;

	flags = 0;
	while (ft_isspace((*(*l_cmd))))
		l_cmd[0]++;
	if (*(*l_cmd) == 'e' && *(*l_cmd + 1) == 'n' && *(*l_cmd + 2) == 'v' &&
			*(*l_cmd + 3) == ' ')
	{
		l_cmd[0] += 4;
		if (change_flag(&flags, l_cmd) == false)
			return (OPT_WRONG);
	}
	return (flags);
}

static int					error_env(char flags, char *l_cmd)
{
	if (flags == OPT_WRONG)
	{
		ft_putstr("env: illegal option -- ");
		ft_putchar(*l_cmd);
		ft_putchar('\n');
	}
	else if (flags == PARAM)
		ft_putendl("env: option requires an argument -- u");
	return (ERROR);
}

int							builtin_env(char *l_cmd)
{
	char					flags;
	char					**tab;
	int						ret;

	tab = NULL;
	if ((flags = get_flags_env(&l_cmd)) == PARAM || flags == OPT_WRONG)
		return (error_env(flags, l_cmd));
	if ((flags & FLAG_I) != 0)
		ret = tab_env_i(&l_cmd, &tab);
	else if ((flags & FLAG_U) != 0)
		ret = tab_env_u(&l_cmd, &tab);
	else
		ret = tab_env(&l_cmd, &tab);
	ft_putendl(l_cmd);
	return (true);
}
