/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 21:31:27 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:27:44 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

#define SIZE_BUFF_M 90

static int					count_objets(char *path, char *begin_name)
{
	int						count;
	size_t					len;
	DIR						*dirent;
	struct dirent			*str_dirent;

	if (path == NULL || path[0] == '\0' || begin_name == NULL)
		return (ERROR);
	len = ft_strlen(begin_name);
	if (access(path, F_OK | R_OK | X_OK) != 0)
		return (false);
	count = 0;
	if ((dirent = opendir(path)) != NULL)
	{
		while ((str_dirent = readdir(dirent)) != NULL)
		{
			if (len == 0)
				count++;
			else if (ft_strncmp(str_dirent->d_name, begin_name, len) == 0)
				count++;
		}
		closedir(dirent);
	}
	return (count);
}

static char					*get_path_with_begin(t_entry *c)
{
	char					mem[SIZE_BUFF_M + 1];
	char					*tmp;
	char					*buff;
	int						i;

	if (c == NULL || c->c == ' ')
		return (c == NULL ? NULL : ft_strdup("./"));
	tmp = NULL;
	buff = NULL;
	while (c != NULL && c->c != ' ' && (i = SIZE_BUFF_M) == SIZE_BUFF_M)
	{
		ft_bzero((void *)mem, sizeof(mem));
		while (c != NULL && c->c != ' ' && i > 0)
		{
			mem[--i] = c->c;
			c = c->prev;
		}
		if ((tmp = ft_strjoin(&mem[i], buff)) == NULL)
			return (NULL);
		if (buff != NULL)
			ft_memdel((void**)&buff);
		buff = tmp;
	}
	return (buff);
}

static int					put_list_objets(char **list_obj, char *begin)
{
	char					*resul;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	resul = print_list_term(sh, list_obj, true);
	return (add_word_to_g_line(&resul, begin));
}

static int					get_path_begin(t_entry *c, char **path, char **bgin)
{
	char					*path_begin;
	char					*addr;
	size_t					len;

	if (c == NULL || path == NULL || bgin == NULL ||
			(path_begin = get_path_with_begin(c)) == NULL)
		return (ERROR);
	if ((addr = ft_strrchr(path_begin, '/')) == NULL)
	{
		*path = ft_strdup("./");
		*bgin = ft_strdup(path_begin);
	}
	else
	{
		len = addr - path_begin;
		*path = ft_strndup(path_begin, len + 1);
		*bgin = ft_strdup(&path_begin[len + 1]);
	}
	if (*path == NULL || *bgin == NULL)
		return (ERROR);
	ft_memdel((void**)&path_begin);
	return (true);
}

int							autocompletion_path(t_entry *c)
{
	char					*begin;
	char					*path;
	char					**list_obj;
	int						nb_obj;
	size_t					len;

	if (c == NULL || get_path_begin(c, &path, &begin) == ERROR)
		return (ERROR);
	if ((nb_obj = count_objets(path, begin)) == ERROR || begin == NULL ||
			del_car_begin_in_g_line(ft_strlen(begin)) == ERROR)
		return (ERROR);
	if (nb_obj > 0)
	{
		if ((list_obj = make_list_object(path, begin, nb_obj)) == NULL ||
				put_list_objets(list_obj, begin) == ERROR)
			return (ERROR);
		ft_free_strsplit(list_obj);
	}
	if ((len = ft_strlen(path)) == 0 || begin == path)
		return (ERROR);
	ft_memdel((void**)&path);
	ft_memdel((void**)&begin);
	return (true);
}
