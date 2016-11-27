/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 18:25:34 by fpasquer          #+#    #+#             */
/*   Updated: 2016/11/27 09:46:24 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>

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

static void					put_line_entre(char *line)
{
	int						i;
	t_21sh					*sh;

	if (line != NULL && line[0] != '\0' && line[0] != '\n')
	{
		if ((sh = get_21sh(NULL)) == NULL)
			return ;
		if (put_cmd_term("cb") == ERROR)
			return ;
		i = 0;
		while (i++ < sh->len_prompt)
			ft_putchar(' ');
		ft_putstr(COLOR_LINE);
		ft_putstr(line);
		ft_putstr(RESET_COLOR);
		sh->pos = 0;
		del_g_lines();
	}
}


int							print_prompt(void)
{
	char					promt[SIZE_PROMT + 5];
	char					*ret;
	t_21sh					*sh;

	if ((ret = tgetstr("sc", NULL)) == NULL)
		return (false);
	tputs(ret, 0, my_out_put);
	if (getcwd(promt, SIZE_PROMT) == NULL || (sh = get_21sh(NULL)) == NULL)
		return (false);
	if (ft_strcat(promt, " ?> ") == NULL)
		return (false);
	ft_putstr(COLOR_POMT);
	ft_putstr(promt);
	ft_putstr(RESET_COLOR);
	sh->len_prompt = ft_strlen(promt);
	return (true);
}

static int					at_save_history(char *line)
{
	int						i;
	bool					ret;

	if (line == NULL)
		return (ERROR);
	i = 0;
	ret = false;
	while (line[i] != '\0')
		ret = (ft_isspace(line[i++]) == true) ? ret : true;
	return (ret);
}

static int					exe_cmd(char *line)
{
	t_21sh					*sh;

	if (line == NULL || (sh = get_21sh(NULL)) == NULL || sh->hist == NULL)
		return (ERROR);
	if (at_save_history(line) == true)
		if (add_history(&sh->hist, line) == ERROR)
			return (ERROR);
	if (tcsetattr(0, TCSADRAIN, &sh->reset) == -1)
		return (ERROR);
	//partie flo
	if (tcsetattr(0, TCSADRAIN, &sh->term_param) == -1)
		return (ERROR);
	return (true);
}

void						loop_shell(void)
{
	char					*line;
	int						ret;
	t_21sh					*sh;

	line = NULL;
	g_lines = NULL;
	if ((sh = get_21sh(NULL)) != NULL)
	{
		print_header();
		while (print_prompt())
		{
			if ((line = get_line_entree()) == NULL)
				break ;
			put_line_entre(line);
			if (exe_cmd(line) == ERROR)
				break ;
			ft_memdel((void**)&line);
		}
		del_21sh();
	}
}
