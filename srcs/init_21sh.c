/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_21sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 09:22:44 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 17:23:00 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/21sh.h"

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
	ft_memdel((void**)sh);
	return (true);
}

static int					save_sh_init(char *name, char **dest)
{
	char					*tmp;
	extern char				**environ;

	if ((tmp = ft_getenv(environ, name)) == NULL)
		return (false);
	if (((*dest) = ft_strdup(tmp)) == NULL)
		return (false);
	return (true);
}

t_21sh						*get_21sh(t_21sh *shell_21sh)
{
	static t_21sh			*adr_21sh;

	if (shell_21sh != NULL)
		adr_21sh = shell_21sh;
	return (adr_21sh);
}

t_21sh						*init_21sh(void)
{
	char					*tmp;
	extern char				**environ;
	t_21sh					*sh;

	if ((sh = ft_memalloc(sizeof(*sh))) == NULL)
		return (NULL);
	if (save_sh_init("TERM", &sh->term_name) == false)
		return (NULL);
	if (save_sh_init("OLDPWD", &sh->old_pwd) == false)
		if ((sh->old_pwd = ft_strdup("")) == NULL)
			return (NULL);
	if (save_sh_init("HOME", &sh->home) == false)
		if (save_pwd(&sh->home) == ERROR)
			return (NULL);
	if (save_pwd(&sh->pwd) == ERROR)
		return (NULL);
	save_sh_init("USER", &sh->user);
	if (save_path(&sh, ft_getenv(environ, "PATH")) == ERROR)
			return (NULL);
	return (get_21sh(sh));
}

int							del_21sh(void)
{
	t_21sh					*shell_21sh;

	if ((shell_21sh = get_21sh(NULL)) != NULL)
		return (del_struct_21sh(&shell_21sh));
	return (ERROR);
}
