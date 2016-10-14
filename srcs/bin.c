/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 17:00:14 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/13 21:42:00 by fpasquer         ###   ########.fr       */
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
	return (true);
}

static int					add_bin_directory(t_21sh *sh, char *path)
{
	int						ret;
	DIR						*direct;
	struct dirent			*str_dirent;

	//	if ((ret = access(path, F_OK | R_OK | X_OK)) != 0)
	//		return (ERROR);

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
	i = 0;
	/*while (i < SIZE_HASH)
		if (sh->hash[i++] != NULL)
			sort_list(&sh->hash[i - 1], len_tri);*/
	return (true);
}

static int					print_bin_list(t_bin *lst)
{
	int						loop;
	t_bin					*tmp;

	tmp = lst;
	loop = 0;
	while (tmp != NULL)
	{
		loop++;
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
	if (loop > 0)
		ft_putchar('\n');
	return (loop);
}

int							print_all_bin(void)
{
	int						index;
	int						loop;
	int						mem;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (-1);
	index = 0;
	loop = 0;
	mem = 0;
	while (index < SIZE_HASH)
	{
		loop = print_bin_list(sh->hash[index++]);
		mem = (mem < loop) ? loop : mem;
	}
	if (mem != 0)
	{
		ft_putstr("le nombre max de loop est ");
		ft_putnbr(mem);
		ft_putchar('\n');
	}
	else
		ft_putendl("Pas de Binaire");
	return (true);
}
