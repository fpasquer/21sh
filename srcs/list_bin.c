/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 17:10:58 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/19 18:29:59 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static int					count_objets(char *path, char *begin_name)
{
	int						count;
	size_t					len;
	DIR						*dirent;
	struct dirent			*str_dirent;

	if (path == NULL || begin_name == NULL)
		return (ERROR);
	len = ft_strlen(begin_name);
	if (access(path, F_OK | R_OK | X_OK) != 0)
		return (ERROR);
	count = 0;
	if ((dirent = opendir(path)) != NULL)
	{
		while ((str_dirent = readdir(dirent)) != NULL)
			if (len == 0)
				count++;
			else
				if (ft_strncmp(str_dirent->d_name, begin_name, len) == 0)
					count++;
		closedir(dirent);
	}
	return (count);
}

static char					**save_list(char ***list, char *path,
		char *begin_name)
{
	int						i;
	size_t					len;
	DIR						*dirent;
	struct dirent			*str_dirent;

	if (list == NULL || path == NULL || begin_name == NULL)
		return (NULL);
	len = ft_strlen(begin_name);
	if (access(path, F_OK | R_OK | X_OK) != 0)
		return (NULL);
	i = 0;
	if ((dirent = opendir(path)) != NULL)
	{
		while ((str_dirent = readdir(dirent)) != NULL)
			if (len == 0 ||
					ft_strncmp(str_dirent->d_name, begin_name, len) == 0)
			{
				if ((list[0][i++] = ft_strdup(str_dirent->d_name)) == NULL)
					break;
			}
		closedir(dirent);
	}
	return (*list);
}

static char					**make_list_bin(char *path, char *begin_name,
		int count)
{
	char					**list_bin;

	if (path == NULL || begin_name == NULL)
		return (NULL);
	if (count == 0)
		return (ft_memalloc(sizeof(*list_bin)));
	if ((list_bin = ft_memalloc(sizeof(*list_bin) * (count + 1))) == NULL)
		return (NULL);
	return (save_list(&list_bin, path, begin_name));
}

int							list_all_bin(char *path, char *begin_name)
{
	char					**list_bin;
	char					*ret;
	int						count;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || path == NULL || begin_name == NULL)
		return (ERROR);
	if ((count = count_objets(path, begin_name)) == ERROR)
		return (ERROR);
	if ((list_bin = make_list_bin(path, begin_name, count)) == NULL)
		return (ERROR);
	ret = print_list_term(sh, list_bin, true);
	ft_free_strsplit(list_bin);
	return (put_pompt_word(&ret));
}
