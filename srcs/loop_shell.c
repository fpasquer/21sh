/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 15:09:24 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/13 01:49:57 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

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
	put_line_header("TERM_NAME", sh->term_name);
	put_line_header("HOME", sh->home);
	put_line_header("PWD", sh->pwd);
	put_line_header("OLDPWD", sh->old_pwd);
	put_line_header("USER", sh->user);
	put_line_header("PATH", sh->path);
	ft_putstr("SHLVL=");
	ft_putnbr(sh->sh_lvl);
	ft_putstr("\nNB_VAR_ENV=");
	ft_putnbr(sh->nb_var_env);
	ft_putstr("\nWIM_ROW=");
	ft_putnbr(sh->win.ws_row);
	ft_putstr(" WIN_COLUMN=");
	ft_putnbr(sh->win.ws_col);
	ft_putstr("\n\n");
	return (true);
}

static int					print_prompt(void)
{
	char					promt[SIZE_PROMT + 5];
	t_21sh					*sh;

	if (getcwd(promt, SIZE_PROMT) == NULL || (sh = get_21sh(NULL)) == NULL)
		return (false);
	if (ft_strcat(promt, " ?> ") == NULL)
		return (false);
	ft_putstr(COLOR_POMT);
	ft_putstr(promt);
	ft_putstr(RESET_COLOR);
	return (true);
}

static void					put_line_entre(char *line)
{
	ft_putstr(COLOR_LINE);
	ft_putstr(line);
	ft_putendl(RESET_COLOR);
}

/*
**
*/

void						loop_shell(void)
{
	char					*line;
	int						ret;
	t_cmd 					*cmd;
	t_cmd 					*head;

	line = NULL;
	cmd = NULL;
	print_header();
	while (print_prompt())
	{
		if ((line = get_line_entree()) == NULL)
			break ;
		put_line_entre(line);
		
		if ((cmd = parse_cmd(line)) != NULL)
		{
			head = cmd;
			print_cmd(cmd);
			while (cmd && cmd->arg && cmd->arg[0] != NULL)
			{
				builtin_or_not(cmd);
				cmd = cmd->right;
			}
			free_cmd(head);
		}
		// stin_content = parse_stin(line); // fonction temporaire
		// free_stin(&stin_content); // fonction temporaire
		
		ft_memdel((void**)&line);
	}
	del_21sh();
}
