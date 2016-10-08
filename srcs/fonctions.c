/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:32:47 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 17:10:30 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/21sh.h"

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
		return (false);
	if ((*sh)->path != NULL)
		ft_memdel((void**)&(*sh)->path);
	if ((*sh)->tab_path != NULL)
		ft_free_strsplit((*sh)->tab_path);
	if (((*sh)->path = ft_strdup(path)) == NULL)
		return (ERROR);
	if (((*sh)->tab_path = ft_strsplit(path, ':')) == NULL)
		return (ERROR);
	return (true);
}
