/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:25:40 by fcapocci          #+#    #+#             */
/*   Updated: 2016/12/29 17:25:41 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

#include <stdio.h>

static int					moove_l_cmd(char **l_cmd)
{
	char					*tmp_line;
	int						i;
	bool					egal_find;

	if (l_cmd == NULL)
		return (ERROR);
	i = 0;
	egal_find = false;
	tmp_line = *l_cmd;
	while (tmp_line[i] != '\0')
	{
		while (ft_isspace(tmp_line[i]))
			i++;
		l_cmd[0] += (tmp_line + i) - l_cmd[0];
		egal_find = false;
		while (tmp_line[i] != '\0' && tmp_line[i] != ' ')
			egal_find = (tmp_line[i++] == '=') ? true : egal_find;
		if (egal_find == false)
			break ;
		l_cmd[0] += (tmp_line + i) - l_cmd[0];
	}
	return (true);
}

static t_env				*get_at_add(char **list_env)
{
	int						i;
	t_env					*at_add;

	if (list_env == NULL)
		return (NULL);
	at_add = NULL;
	i = 0;
	while (list_env[i++])
	{
		if (ft_strchr(list_env[i - 1], '=') == NULL)
			break ;
		if ((add_env(&at_add, list_env[i - 1], i - 1, true)) == ERROR)
			return (NULL);
	}
	return (at_add);
}

static int					len_list_env(t_env *lst)
{
	int						count;
	t_env					*curs;

	curs = lst;
	count = 0;
	while (curs != NULL)
	{
		curs = curs->next;
		count++;
	}
	return (count);
}

static int					add_in_tab(int i, char **tab, t_env *lst)
{
	t_env					*curs;

	if (tab == NULL || i < 0)
		return (ERROR);
	curs = lst;
	while (curs != NULL)
	{
		if (curs->add == true)
			if (!(tab[i++] = ft_multijoin(3, curs->name, "=", curs->value)))
				return (ERROR);
		curs = curs->next;
	}
	return (i);
}

char						**get_new_tab(t_env *lst_1, t_env *lst_2)
{
	char					**tab;
	int						count;
	int						i;

	if ((count = len_list_env(lst_1) + len_list_env(lst_2)) <= 0)
		return (NULL);
	if ((tab = ft_memalloc(sizeof(char *) * (count + 1))) == NULL)
		return (NULL);
	i = 0;
	if ((i = add_in_tab(i, tab, lst_1)) == ERROR)
		return (NULL);
	if ((i = add_in_tab(i, tab, lst_2)) == ERROR)
		return (NULL);
	return (tab);
}

static int					save_tab_env(t_env *base, char **l_cmd, char ***tab)
{
	char					**new_env;
	t_env					*at_add;

	if ((new_env = ft_strsplit(*l_cmd, ' ')) == NULL)
		return (ERROR);
	if (moove_l_cmd(l_cmd) == false)
		return (ERROR);
	at_add = get_at_add(new_env);
	tab[0] = get_new_tab(base, at_add);
	if (at_add != NULL)
		del_list_env(&at_add);
	ft_free_strsplit(new_env);
	return (true);
}

int							tab_env_i(char **l_cmd, char ***tab)
{
	return (save_tab_env(NULL, l_cmd, tab));
}

int							tab_env_u(char **l_cmd, char ***tab)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	return (save_tab_env(sh->env, l_cmd, tab));
}

int							tab_env(char **l_cmd, char ***tab)
{
	t_env					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	curs = sh->env;
	while (curs != NULL)
	{
		curs->add = true;
		curs = curs->next;
	}
	return (save_tab_env(sh->env, l_cmd, tab));
}
