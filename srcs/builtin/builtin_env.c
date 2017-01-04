/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:50:51 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/04 15:00:22 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#define FLAG_I 1
#define FLAG_P 2
#define FLAG_S 4
#define FLAG_U 8
#define FLAG_V 16

#define OPT_WRONG -2
#define PARAM -3

#include <stdio.h>

static int					option_u_env(char **l_cmd)
{
	char					*end;
	int						decalage;

	if (l_cmd != NULL && ft_strncmp(*l_cmd, "u ", 2) == 0)
	{
		l_cmd[0] += 2;
		while (ft_isspace((*(*l_cmd))))
			l_cmd[0]++;
		if ((*(*l_cmd)) == '\0')
			return (PARAM);
		if ((end = ft_strchr(*l_cmd, ' ')) == NULL)
			end = l_cmd[0] + ft_strlen(*l_cmd);
		decalage = (*end == '\0') ? -1 : 0;
		*end = '\0';
		check_if_env_exist(*l_cmd);
		l_cmd[0] = end + decalage;
		return (true);
	}
	return (PARAM);
}

static int					change_flag(char *flags, char **l_cmd)
{
	if (flags == NULL || l_cmd == NULL)
		return (ERROR);
	while ((*(*l_cmd)) == '-' || (*(*l_cmd)) == ' ')
		if ((*(*l_cmd)++) == '-')
		{
			if ((*(*l_cmd)) == 'i')
				*flags = *flags | FLAG_I;
			else if ((*(*l_cmd)) == 'u')
			{
				*flags = *flags | FLAG_U;
				if (option_u_env(l_cmd) == PARAM)
					return (PARAM);
			}
			else
				return (OPT_WRONG);
			l_cmd[0]++;
		}
	return (true);
}

static char					get_flags_env(char **l_cmd)
{
	char					flags;
	int						ret;
	t_env					*curs;
	t_21sh					*sh;

	flags = 0;
	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	curs = sh->env;
	while (curs != NULL)
	{
		curs->add = true;
		curs = curs->next;
	}
	while (ft_isspace((*(*l_cmd))))
		l_cmd[0]++;
	if (*(*l_cmd) == 'e' && *(*l_cmd + 1) == 'n' && *(*l_cmd + 2) == 'v' &&
			*(*l_cmd + 3) == ' ')
	{
		l_cmd[0] += 4;
		if ((ret = change_flag(&flags, l_cmd)) == OPT_WRONG || ret == PARAM)
			return (ret);
	}
	return (flags);
}

static int					error_env(char flags, char *l_cmd)
{
	if (flags == OPT_WRONG)
	{
		ft_putstr_fd("env: illegal option -- ", STDERR_FILENO);
		ft_putchar_fd(*l_cmd, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (flags == PARAM)
		ft_putendl_fd("env: option requires an argument -- u", STDERR_FILENO);
	return (ERROR);
}

int							builtin_env(t_cmd *content)
{
	char					flags;
	char					**tab;
	int						ret;
	char					*tmp_line;
	int						i;

	i = 0;
	tmp_line = content->line;
	tab = NULL;
	if ((flags = get_flags_env(&tmp_line)) == PARAM || flags == OPT_WRONG)
		return (error_env(flags, content->line));
	if (flags == ERROR)
		return (ERROR);
	if ((flags & FLAG_I) != 0)
		ret = tab_env_i(&tmp_line, &tab);
	else if ((flags & FLAG_U) != 0)
		ret = tab_env_u(&tmp_line, &tab);
	else
		ret = tab_env(&tmp_line, &tab);
	if (ret == ERROR)
		return (-1);
	if (tab != NULL)
	{
		while (tab[i] != NULL)
			ft_putendl_fd(tab[i++], STDOUT_FILENO);
		ft_free_strsplit(tab);
	}
	return (true);
}
