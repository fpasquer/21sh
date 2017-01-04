/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:08:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/04 16:24:58 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

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
