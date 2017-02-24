/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:08:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/24 19:37:16 by fcapocci         ###   ########.fr       */
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

int							tab_env_u(char **l_cmd, char ***tab, t_env *sub_env)
{
	t_21sh					*sh;

	/*t_env *cpy = sub_env;
	if (cpy == NULL)
		fprintf(debug, "cpy == NULL\n");
	else
	{
		while (cpy)
		{
			fprintf(debug, "%s=%s\n", cpy->name, cpy->value);
			cpy = cpy->next;
		}
	}*/
	fprintf(debug, "pass -u\n");
	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	return (save_tab_env(sub_env ? sub_env : sh->env, l_cmd, tab));
}

int							tab_env(char **l_cmd, char ***tab, t_env *sub_env)
{
	t_env					*curs;
	t_21sh					*sh;

	/*t_env *cpy = sub_env;
	if (cpy == NULL)
		fprintf(debug, "cpy == NULL\n");
	else
	{
		while (cpy)
		{
			fprintf(debug, "%s=%s\n", cpy->name, cpy->value);
			cpy = cpy->next;
		}
	}*/
	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	curs = sub_env ? sub_env : sh->env;
	while (curs != NULL)
	{
		curs->add = true;
		curs = curs->next;
	}
	return (save_tab_env(sub_env ? sub_env : sh->env, l_cmd, tab));
}

int							print_env(char **tab)
{
	int						i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
			ft_putendl_fd(tab[i++], STDOUT_FILENO);
		ft_free_strsplit(tab);
	}
	return (true);
}
