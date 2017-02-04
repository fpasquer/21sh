/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:30:40 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/04 18:32:09 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include <stdio.h>

static int					match(char *name, char **tab)
{
	unsigned int			i;

	if (name == NULL || tab == NULL)
		return (0);
	i = 0;
	while (tab[i] != NULL)
		if (ft_strcmp(tab[i++], name) == 0)
			return (true);
	return (false);
}

int							nb_match_var_env(char **tab)
{
	int						nb_match_val;
	t_env					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (0);
	nb_match_val = 0;
	curs = sh->env;
	while (curs != NULL)
	{
		if (match(curs->name, tab) == true)
			nb_match_val++;
		curs = curs->next;
	}
	return (nb_match_val);
}

int							save_pwd(char **dest)
{
	if (dest == NULL)
		return (ERROR);
	if ((*dest = ft_memalloc(sizeof(char) * (LEN_PATH_MAX + 1))) == NULL)
		return (ERROR);
	if (getcwd(*dest, LEN_PATH_MAX) == NULL)
		return (ERROR);
	return (true);
}

int							save_path(t_21sh **sh, char *path)
{
	if (sh == NULL || *sh == NULL)
		return (ERROR);
	if (path == NULL)
	{
		if ((*sh)->path != NULL)
			ft_memdel((void**)&(*sh)->path);
		if (((*sh)->path = ft_strdup("")) == NULL)
			return (ERROR);
		return (false);
	}
	if ((*sh)->path != NULL)
		ft_memdel((void**)&(*sh)->path);
	if ((*sh)->tab_path != NULL)
		ft_free_strsplit((*sh)->tab_path);
	if (((*sh)->path = ft_strdup(path)) == NULL)
		return (ERROR);
	if (((*sh)->tab_path = ft_strsplit(path, ':')) == NULL)
		return (ERROR);
	return (save_bin(*sh));
}
