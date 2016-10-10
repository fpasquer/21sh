/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 14:07:56 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/10 14:43:37 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

#include <stdio.h>

static int					mush_be_save(char **lst_del, char *env)
{
	int						i;

	if (lst_del == NULL || env == NULL)
		return (ERROR);
	i = 0;
	while (lst_del[i] != NULL)
		if (ft_strcmp(lst_del[i++], env) == 0)
			return (i - 1);
	return (-1);
}

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
			break;
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
		if ((add_env(&at_add, list_env[i - 1], i - 1)) == ERROR)
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

static int					add_in_tab(int i, char ***tab, t_env *lst)
{
	t_env					*curs;

	if (tab == NULL)
		return (ERROR);
	curs = lst;
	while (curs != NULL)
	{
		if (curs->add == false) // a changer par true
			if (!(tab[0][i++] = ft_multijoin(3, curs->name, "=", curs->value)))
				return (ERROR);
		curs = curs->next;
	}
	return (true);
}

char						**get_new_tab(t_env *lst_1, t_env *lst_2)
{
	char					**tab;
	int						count;
	int						i;

	if ((count = len_list_env(lst_1) + len_list_env(lst_2)) <= 0)
		return (NULL);
	if ((tab = ft_memalloc(sizeof(char*) * (count + 1))) == NULL)
		return (NULL);
	if ((i = add_in_tab(0, &tab, lst_1)) == ERROR)
		return (NULL);
	if ((i = add_in_tab(i, &tab, lst_2)) == ERROR)
		return (NULL);
	return (tab);
}

int							tab_env_i(char **l_cmd, char ***tab)
{
	char					**new_env;
	t_env					*at_add;

	if ((new_env = ft_strsplit(*l_cmd, ' ')) == NULL)
		return (ERROR);
	if (moove_l_cmd(l_cmd) == false)
		return (ERROR);
	if ((at_add = get_at_add(new_env)) == NULL)
		return (ERROR);
	if ((*tab = get_new_tab(NULL, at_add)) == NULL)
		return (ERROR);
	del_list_env(&at_add);
	ft_free_strsplit(new_env);
	return (true);
}

int							tab_env_u(char **l_cmd, char ***tab)
{
	char					**new_env;
	t_env					*at_add;

	if ((new_env = ft_strsplit(*l_cmd, ' ')) == NULL)
		return (ERROR);
	if (moove_l_cmd(l_cmd) == false)
		return (ERROR);
	if ((at_add = get_at_add(new_env)) == NULL)
		return (ERROR);
	if ((*tab = get_new_tab(NULL, at_add)) == NULL)
		return (ERROR);
	del_list_env(&at_add);
	ft_free_strsplit(new_env);
	return (true);

}

int							tab_env(char **l_cmd, char ***tab)
{
	return (true);
}
