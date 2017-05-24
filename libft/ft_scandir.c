/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scandir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 10:09:02 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/24 10:09:30 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	DESCRIPTION :
**		int ft_scandir(char *path, char ***list)
**		enregistre dans list le contenu du dossier ou path pointe
**	PARAMETRE :
**		path : path du dossier
**		list : pointeur d'un tableau 2d
**	RETOUR :
**		le nombre de chose contenu dans le dossier
**		-1 si il y a un Erreur
*/

int							ft_scandir(char *path, char ***list)
{
	char					*tmp;
	int						ret;
	DIR						*direct;
	struct dirent			*str_dirent;

	if (path == NULL || list == NULL || ft_is_dir(path) <= 0 ||
			access(path, F_OK | R_OK | X_OK) != 0 ||
			(direct = opendir(path)) == NULL)
		return (-1);
	ret = 0;
	while ((str_dirent = readdir(direct)) != NULL)
	{
		if ((tmp = ft_strdup(str_dirent->d_name)) == NULL)
				break ;
		ret++;
			*list = ft_add_to_array(tmp, *list);
	}
	if (direct != NULL)
		closedir(direct);
	return (ret);
}

