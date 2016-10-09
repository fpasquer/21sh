/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 15:09:24 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/09 18:34:16 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

static int					put_line_header(char *name, char *value)
{
	if (name == NULL)
		return (false);
	ft_putstr(name);
	ft_putstr(" = ");
	ft_putendl((value == NULL) ? "Vide" : value);
	return (true);
}

static int					print_header(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (false);
	put_line_header("HOME", sh->home);
	put_line_header("PWD", sh->pwd);
	put_line_header("OLDPWD", sh->old_pwd);
	put_line_header("USER", sh->user);
	put_line_header("PATH", sh->path);
	return (true);
}

static int					print_prompt(void)
{
	char					prompt[SIZE_PROMT + 5];
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || getcwd(prompt, SIZE_PROMT) == NULL)
		return (false);
	return (true);
}

void						loop_shell(void)
{
	print_header();
	while (print_prompt())
	{
		;
	}
}
