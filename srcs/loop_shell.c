/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 15:09:24 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/11 14:49:07 by fpasquer         ###   ########.fr       */
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
** FONCTION TEMPORAIRE
*/

void 					free_stin(t_stin_content *content)
{
	int 				i = 0;

	if (content->bin_argv) {
		while (content->bin_argv[i]) {
			free(content->bin_argv[i]);
			i++;
		}
		free(content->bin_argv);
	}
}

/*
**
*/

void						loop_shell(void)
{
	char					*line;
	int						ret;
	t_cmd 					*cmd;

	print_header();
	while (print_prompt())
	{
		if ((line = get_line_entree()) == NULL)
			break ;
		put_line_entre(line);
		
		cmd = parse_cmd(line);
		print_cmd(cmd);
		// stin_content = parse_stin(line); // fonction temporaire
		// builtin_or_not(&stin_content);
		// free_stin(&stin_content); // fonction temporaire
		
		ft_memdel((void**)&line);
	}
	del_21sh();
}