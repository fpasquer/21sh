/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 09:30:35 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/09 14:12:25 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
# define FLAG_I 1
# define FLAG_P 2
# define FLAG_S 4
# define FLAG_U 8
# define FLAG_V 16

# define OPT_WRONG -2

static char					get_flags_env(char  **l_cmd)
{
	char					c_prev;
	char					flags;
	int						loop;

	flags = 0;
	while (ft_isspace((*(*l_cmd))))
		l_cmd[0]++;
	c_prev = 0;
	if (*(*l_cmd) == 'e' && *(*l_cmd + 1) == 'n' && *(*l_cmd + 2) == 'v')
	{
		loop = 0;
		l_cmd[0] += 3;
		while ((*(*l_cmd)) == '-' || (*(*l_cmd)) == 'i' || (*(*l_cmd)) == 'u'
				|| ft_isspace((*(*l_cmd))))
		{
			flags = ((*(*l_cmd)) == 'i') ? flags | FLAG_I : flags;
			flags = ((*(*l_cmd)) == 'u') ? flags | FLAG_U : flags;
			c_prev = (*(*l_cmd));
			l_cmd[0]++;
			loop++;
		}
	}
	l_cmd[0] = (c_prev == '-') ? l_cmd[0] - 1 : l_cmd[0];
	return ((c_prev != ' ' && loop > 0) ? OPT_WRONG : flags);
}

int							get_tab_env(char *l_cmd, char ***tab)
{
	char					flags;

	if (l_cmd == NULL)
		return (ERROR);
	if ((flags = get_flags_env(&l_cmd)) == OPT_WRONG)
	{
		ft_putstr("env: illegal option -- ");
		ft_putchar(*l_cmd);
		ft_putchar('\n');
		return (ERROR);
	}
	if ((flags & FLAG_I) != 0)
		return (tab_env_i(l_cmd, tab));
	else if ((flags & FLAG_U) != 0)
	{
		if (*l_cmd == '\0')
		{
			ft_putendl("env: option requires an argument -- u");
			return (ERROR);
		}
		return (tab_env_u(l_cmd, tab));
	}
	else
		return (tab_env(l_cmd, tab));
}
