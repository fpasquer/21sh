/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_21sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 09:22:44 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 21:46:16 by fpasquer         ###   ########.fr       */
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
	if ((*sh)->user != NULL)
		ft_memdel((void**)&(*sh)->user);
	if ((*sh)->pwd != NULL)
		ft_memdel((void**)&(*sh)->pwd);
	del_bin();
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

t_21sh						*init_21sh2(t_21sh **sh)
{
	char					*sh_lvl;
	extern char				**environ;

	if ((sh_lvl = ft_getenv(environ, "SHLVL")) == NULL || !ft_is_number(sh_lvl))
		(*sh)->sh_lvl = 1;
	else
		(*sh)->sh_lvl = ft_atoi(sh_lvl) + 1;
	return (get_21sh(*sh));
}


t_21sh						*init_21sh(void)
{
	char					*tmp;
	extern char				**environ;
	t_21sh					*sh;

	if ((sh = ft_memalloc(sizeof(*sh))) == NULL)
		return (NULL);
	if (save_sh_init("TERM", &sh->term_name) == false)
		if ((sh->term_name = ft_strdup(NAME_SHELL)) == NULL)
			return (NULL);
	if (save_sh_init("OLDPWD", &sh->old_pwd) == false)
		if ((sh->old_pwd = ft_strdup("")) == NULL)
			return (NULL);
	if (save_sh_init("HOME", &sh->home) == false)
		if ((sh->home = ft_strdup("")) == NULL)
			return (NULL);
	if (save_pwd(&sh->pwd) == ERROR)
		return (NULL);
	if (save_sh_init("USER", &sh->user) == false)
		if ((sh->user = ft_strdup("")) == NULL)
			return (NULL);;
	if (save_path(&sh, ft_getenv(environ, "PATH")) == ERROR)
			return (NULL);
	return (init_21sh2(&sh));
}

int							del_21sh(void)
{
	t_21sh					*shell_21sh;

	if ((shell_21sh = get_21sh(NULL)) != NULL)
		return (del_struct_21sh(&shell_21sh));
	return (ERROR);
}
