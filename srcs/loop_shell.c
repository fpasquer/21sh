/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 15:09:24 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/20 21:13:20 by fcapocci         ###   ########.fr       */
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

static void					put_line_entre(char *line)
{
	int						i;
	t_21sh					*sh;

	if (line != NULL && line[0] != '\0' && line[0] != '\n')
	{
		if ((sh = get_21sh(NULL)) == NULL)
			return ;
		i = g_lines.len / sh->win.ws_col;
		put_cmd_term("cd");
		while (i-- > 0)
			if (put_cmd_term("kd") == ERROR)
				return ;
		//je ne comprends pas pourquoi j' ai des B qui pop
		i = sh->win.ws_col;
		while (i-- > 0)
			put_cmd_term("le");
		//pour moi la boucle du dessus est a supprimer, mais des B peuvent POP sur les commandes sur plusieurs lignes
		i = 0;
		while (i++ < sh->len_prompt)
			ft_putchar(' ');
		ft_putstr(COLOR_LINE);
		ft_putstr(line);
		ft_putendl(RESET_COLOR);
		sh->pos = 0;
		del_g_lines();
	}
}

static int					check_add_hist(t_history **hist, char **line)
{
	if (hist == NULL || line == NULL)
		return (ERROR);
	if (add_history(hist, line) == ERROR)
		return (ERROR);
	return (true);
}

static void					loop_cmd(t_cmd *cmd, t_cmd *head)
{
	while (cmd && cmd->arg && cmd->arg[0] != NULL)
	{
		builtin_or_not(cmd);
		print_cmd(cmd); //DEBUG
		if ((cmd->right && cmd->op == ET && cmd->done != 0)
				|| (cmd->right && cmd->op == OU && cmd->done == 0))
			break ;
		cmd = cmd->right;
	}
	free_cmd(head);
}

void						loop_shell(void)
{
	char					*line;
	int						ret;
	t_21sh					*sh;
	t_cmd 					*cmd;

	line = NULL;
	cmd = NULL;
	del_g_lines();
	if ((sh = get_21sh(NULL)) != NULL)
	{
		print_header();
		while (1)
		{
			if ((line = get_line_entree()) == NULL)
				break ;
			put_line_entre(line);
			if (check_add_hist(&sh->hist, &line) == ERROR)
				break ;
			if ((cmd = parse_cmd(line, NULL, 0)) != NULL)
				loop_cmd(cmd, cmd);
		}
		del_21sh();
	}
}
