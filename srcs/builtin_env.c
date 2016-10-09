/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 09:30:35 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/09 22:00:09 by fpasquer         ###   ########.fr       */
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
	return (((*(*l_cmd)) == '\0' && (flags & FLAG_U) != 0) ? PARAM : flags);
}

static int					get_tab_env(char **l_cmd, char ***tab)
{
	char					flags;

	if (l_cmd == NULL)
		return (ERROR);
	if ((flags = get_flags_env(l_cmd)) == OPT_WRONG)
	{
		ft_putstr("env: illegal option -- ");
		ft_putchar(**l_cmd);
		ft_putchar('\n');
		return (ERROR);
	}
	else if (flags == PARAM)
	{
		ft_putendl("env: option requires an argument -- u");
		return (ERROR);
	}
	if ((flags & FLAG_I) != 0)
		return (tab_env_i(*l_cmd, tab));
	else if ((flags & FLAG_U) != 0)
		return (tab_env_u(l_cmd, tab));
	else
		return (tab_env(*l_cmd, tab));
}

static int					add_in_tab(char ***tab, char *entree)
{
	char					**new_tab;
	unsigned int			i;
	t_21sh					*sh;

	if (tab == NULL || entree == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((new_tab = ft_memalloc(sizeof(char *) * (sh->nb_var_env + 2 ))) == NULL)
		return (ERROR);
	i = 0;
	while (i < sh->nb_var_env && tab[0][i] != NULL)
	{
		new_tab[i] = tab[0][i];
		i++;
	}
	new_tab[i] = ft_strdup(entree);
	*tab = new_tab;
	sh->nb_var_env++;
	return (true);
}

static int					add_new_var_env(char *l_cmd, char ***tab)
{
	char					*egal;
	char					*end;
	int						recul;

	if (l_cmd == NULL || tab == NULL)
		return (false);
	while (ft_isspace(*l_cmd) == true)
		l_cmd++;
	recul = 0;
	while (l_cmd != '\0' && (egal = ft_strchr(l_cmd, '=')) != NULL)
	{
		if ((end = ft_strchr(l_cmd, ' ')) == NULL)
		{
			end = egal + ft_strlen(egal);
			recul = -1;
		}
		*end = '\0';
		if (add_in_tab(tab, l_cmd) == ERROR)
			return (ERROR);
		l_cmd = end + 1 + recul;
	}
	return (true);
}

int							builtin_env(char *l_cmd)
{
	char					**tab;
	int						i;

	if (l_cmd == NULL || get_tab_env(&l_cmd, &tab) == ERROR)
		return (ERROR);
	if (*l_cmd == '\0')
	{
		i = 0;
		while (tab[i] != NULL)
			ft_putendl(tab[i++]);
	}
	else
	{
		if (add_new_var_env(l_cmd, &tab) != true)
			return (ERROR);
		i = 0;
		while (tab[i] != NULL)
			ft_putendl(tab[i++]);
	}
	ft_free_strsplit(tab);
	return (true);
}
