/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:43:31 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/23 18:49:45 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

static char					*list_str(char *path)
{
	char					*ret;
	DIR						*direct;
	struct dirent			*str_dirent;

	fprintf(debug, "path = %s\n", path);
	if ((ret = ft_strdup("")) != NULL && path != NULL &&
			access(path, F_OK | R_OK | X_OK) == 0)
		if ((direct = opendir(path)) != NULL)
		{
			while ((str_dirent = readdir(direct)) != NULL)
			{
				if ((ret = ft_multijoin(3, ret, " ", str_dirent->d_name)) == NULL)
					return (ret);
			}
			closedir(direct);
		}
	return (ret);
}

static char					*path_globbing(char **new_str)
{
	char					*tmp;

	if (new_str == NULL)
		return (NULL);
	if (*new_str != NULL && (tmp = ft_strchr(*new_str, '/')) == NULL)
	{
		tmp = ft_strjoin("./", *new_str);
		ft_memdel((void**)new_str);
		*new_str = tmp;
	}
	else if (*new_str == NULL)
		*new_str = ft_strdup("./");
	return (*new_str);
}

char						*check_globbing(char **new_str, int nb_ht)
{
	char					*tmp;

	if (new_str == NULL)
		return (NULL);
	if (*new_str != NULL && nb_ht == 0 && (tmp = ft_strchr(*new_str, '*'))
			== ft_strrchr(*new_str, '*') && tmp != NULL)
		if ((*new_str = path_globbing(new_str)) != NULL)
		{
			return (*new_str);
			tmp = list_str(*new_str);
			ft_memdel((void**)new_str);
			*new_str = tmp;
			fclose(debug);
			exit(10);
		}
	return (*new_str);
}
