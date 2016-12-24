/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 17:10:58 by fpasquer          #+#    #+#             */
/*   Updated: 2016/12/24 01:18:43 by fcapocci         ###   ########.fr       */
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

static int					check_file(char ***list, char *path, char *name,
		int i)
{
	char					*tmp_path;
	struct stat				stat;

	if (list == NULL || path == NULL || name == NULL || i < 0)
		return (ERROR);
	if (ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0)
	{
		if ((tmp_path = ft_strjoin(path, name)) == NULL)
			return (ERROR);
		ft_bzero(&stat, sizeof(stat));
		if (lstat(tmp_path, &stat) == 0)
		{
			if ((stat.st_mode & S_IFMT) == S_IFDIR)
				list[0][i] = ft_strjoin(name, "/");
			else
				list[0][i] = ft_strdup(name);
			if (list[0][i] == NULL)
				return (ERROR);
		}
		ft_memdel((void**)&tmp_path);
		return (true);
	}
	return (false);
}

static char					**save_list(char ***list, char *path,
		char *begin_name)
{
	int						i;
	int						ret;
	size_t					len;
	DIR						*dirent;
	struct dirent			*str_dir;

	if (list == NULL || path == NULL || begin_name == NULL)
		return (NULL);
	len = ft_strlen(begin_name);
	if (access(path, F_OK | R_OK | X_OK) != 0)
		return (NULL);
	i = 0;
	if ((dirent = opendir(path)) != NULL)
	{
		while ((str_dir = readdir(dirent)) != NULL)
			if (len == 0 || ft_strncmp(str_dir->d_name, begin_name, len) == 0)
			{
				if ((ret = check_file(list, path, str_dir->d_name, i))
						== ERROR)
					break ;
				i = (ret == false) ? i : i + 1;
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

/*int							list_all_bin(char *path, char *begin_name)
{
	char					**list_bin;
	char					*ret;
	int						count;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || path == NULL || begin_name == NULL)
		return (ERROR);
	if ((count = count_objets(path, begin_name)) == ERROR)
		return (ERROR);
	if (count == 0)
		return (insert_word_in_g_line(begin_name));
	if ((list_bin = make_list_bin(path, begin_name, count)) == NULL)
		return (ERROR);
	ret = print_list_term(sh, list_bin, true);
	ft_free_strsplit(list_bin);
	return (put_pompt_word(&ret));
}*/
