/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_del_21sh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:21:14 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/23 09:52:19 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

t_21sh						*get_21sh(t_21sh *shell_21sh)
{
	static t_21sh			*adr_21sh;

	if (shell_21sh != NULL)
		adr_21sh = shell_21sh;
	return (adr_21sh);
}

static int					del_struct_21sh(t_21sh **sh)
{
	if ((*sh)->term_name != NULL)
		ft_memdel((void**)&(*sh)->term_name);
	if ((*sh)->old_pwd != NULL)
		ft_memdel((void**)&(*sh)->old_pwd);
	if ((*sh)->home != NULL)
		ft_memdel((void**)&(*sh)->home);
	if ((*sh)->path != NULL)
		ft_memdel((void**)&(*sh)->path);
	if ((*sh)->tab_path != NULL)
		ft_free_strsplit((*sh)->tab_path);
	if ((*sh)->user != NULL)
		ft_memdel((void**)&(*sh)->user);
	if ((*sh)->pwd != NULL)
		ft_memdel((void**)&(*sh)->pwd);
	if ((*sh)->cpy_tmp != NULL)
		ft_memdel((void**)&(*sh)->cpy_tmp);
	del_bin();
	del_env();
	del_hist();
	ft_memdel((void**)sh);
	return (true);
}

int							del_21sh(void)
{
	t_21sh					*shell_21sh;

	if ((shell_21sh = get_21sh(NULL)) != NULL)
	{
		if (tcsetattr(0, TCSADRAIN, &shell_21sh->reset) == -1)
			return (ERROR);
		return (del_struct_21sh(&shell_21sh));
	}
	return (ERROR);
}
