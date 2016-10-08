/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_21sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 09:22:44 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 10:32:12 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/21sh.h"

static int					del_struct_21sh(t_21sh **shell_21sh)
{
	if ((*shell_21sh)->path != NULL)
		ft_free_strsplit((*shell_21sh)->path);
	if ((*shell_21sh)->path_line != NULL)
		ft_memdel((void**)&(*shell_21sh)->path_line);
	ft_memdel((void**)shell_21sh);
	return (true);
}

t_21sh						*get_21sh(t_21sh *shell_21sh)
{
	static t_21sh			*adr_21sh;

	if (shell_21sh != NULL)
		adr_21sh = shell_21sh;
	return (adr_21sh);
}

t_21sh						*init_21sh(char **env)
{
	t_21sh					*shell_21sh;

	if ((shell_21sh = ft_memalloc(sizeof(*shell_21sh))) == NULL)
		return (NULL);
	if ((shell_21sh->path = ft_strsplit(ft_getenv(env, "PATH"), ':')) == NULL)
		return (NULL);
	if ((shell_21sh->path_line = ft_strdup(ft_getenv(env, "PATH"))) == NULL)
		return (NULL);
	return (get_21sh(shell_21sh));
}

int							del_21sh()
{
	t_21sh					*shell_21sh;

	if ((shell_21sh = get_21sh(NULL)) != NULL)
		return (del_struct_21sh(&shell_21sh));
	return (ERROR);
}
