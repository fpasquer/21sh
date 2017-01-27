/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:29:58 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/27 21:30:00 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

static t_bin				*new_bin(t_bin *lst[], char *name, char *path,
		int index)
{
	t_bin					*n;
	t_bin					*curs;

	if ((n = ft_memalloc(sizeof(*n))) == NULL || name == NULL || path == NULL)
		return (NULL);
	if ((n->name = ft_strdup(name)) &&
			(n->path = ft_strdup(path)) &&
			(n->path_name = ft_multijoin(3, path, "/", name)))
	{
		n->i_hash = index;
		if ((n->len_name = ft_strlen(name)) <= 0)
			return (NULL);
		if ((curs = *lst) == NULL)
			(*lst) = n;
		else
		{
			while (curs->next != NULL)
				curs = curs->next;
			curs->next = n;
		}
		return (n);
	}
	return (NULL);
}

static int					find_name(t_21sh *sh, char *name, char *path)
{
	int						i_hash;
	t_bin					*new;

	if ((i_hash = i_table_hash(name, SIZE_HASH)) == ERROR)
		return (ERROR);
	if ((new = new_bin(&sh->hash[i_hash], name, path, i_hash)) == NULL)
		return (ERROR);
	if (save_dico(&new) == ERROR)
		return (ERROR);
	return (true);
}

static int					add_bin_directory(t_21sh *sh, char *path)
{
	int						ret;
	DIR						*direct;
	struct dirent			*str_dirent;

	if ((ret = access(path, F_OK | R_OK | X_OK)) == 0)
		if ((direct = opendir(path)) != NULL)
		{
			while ((str_dirent = readdir(direct)) != NULL)
				if (find_name(sh, str_dirent->d_name, path) == ERROR)
				{
					closedir(direct);
					return (false);
				}
			if (closedir(direct) == -1)
				return (false);
		}
	return (true);
}

int							save_bin(t_21sh *sh)
{
	unsigned int			i;

	i = 0;
	if (sh == NULL)
		return (false);
	while (sh->tab_path[i] != NULL)
		if (add_bin_directory(sh, sh->tab_path[i++]) == ERROR)
			return (ERROR);
	return (true);
}
