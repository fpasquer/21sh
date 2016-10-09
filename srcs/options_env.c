/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 14:07:56 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/09 14:09:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

static int					mush_be_save(char **lst_del, char *env)
{
	int						i;

	if (lst_del == NULL || env == NULL)
		return (ERROR);
	i = 0;
	while (lst_del[i] != NULL)
		if (ft_strcmp(lst_del[i++], env) == 0)
			return (false);
	return (true);
}

int							tab_env_i(char *l_cmd, char ***tab)
{
	if (tab == NULL)
		return (ERROR);
	if ((*tab = ft_memalloc(sizeof(char *))) == NULL)
		return (ERROR);
	return (true);
}

int							tab_env_u(char *l_cmd, char ***tab)
{
	char					**lst_del;
	int						i;
	t_env					*curs;
	t_21sh					*sh;

	if (tab == NULL || l_cmd == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((lst_del = ft_strsplit(l_cmd, ' ')) == NULL)
		return (ERROR);
	if ((*tab = ft_memalloc(sizeof(char *) * (sh->nb_var_env + 1))) == NULL)
		return (ERROR);
	curs = sh->env;
	i = 0;
	while (curs != NULL)
	{
		if (mush_be_save(lst_del, curs->name) == true)
			if (!(tab[0][i++] = ft_multijoin(3, curs->name, "=", curs->value)))
				return (ERROR);
		curs = curs->next;
	}
	ft_free_strsplit(lst_del);
	return (true);
}

int							tab_env(char *l_cmd, char ***tab)
{
	int						i;
	t_env					*curs;
	t_21sh					*sh;

	if (tab == NULL || l_cmd == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((*tab = ft_memalloc(sizeof(char *) * (sh->nb_var_env + 1))) == NULL)
		return (ERROR);
	curs = sh->env;
	i = 0;
	while (curs != NULL)
	{
		if (!(tab[0][i++] = ft_multijoin(3, curs->name, "=", curs->value)))
			return (ERROR);
		curs = curs->next;
	}
	return (true);
}
