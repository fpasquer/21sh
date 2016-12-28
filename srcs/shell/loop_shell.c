/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 15:09:24 by fpasquer          #+#    #+#             */
/*   Updated: 2016/12/23 22:26:27 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>
/*
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
*/
static void					put_line_entre(char *line)
{
	size_t					i;
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
		ft_putendl(line);
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

static void					loop_cmd(t_cmd *cmd, t_cmd *head)
{
	while (cmd && cmd->arg && cmd->arg[0] != NULL)
	{
		builtin_or_not(cmd, 0, 0);
		//print_cmd(cmd); //DEBUG
		while ((cmd->right && cmd->op == PIP && cmd->done >= 0 
					&& cmd->right->done != -1)
				|| (cmd->right && cmd->op == ET && cmd->done != 0)
				|| (cmd->right && cmd->op == OU && cmd->done == 0))
		{
			ft_putendl_fd("SKIP_CMD", 2);
			ft_putstr_fd("cmd->", 2);
			ft_putstr_fd(cmd->arg[0], 2);
			ft_putstr_fd("== ", 2);
			ft_putnbr_fd(cmd->done, 2);
			ft_putstr_fd("\nlen == ", 2);
			ft_putnbr_fd(ft_strlen(cmd->arg[0]), 2);
			ft_putchar_fd('\n', 2);
			cmd = cmd->right;
		}
		ft_putstr_fd("cmd->", 2);
		ft_putstr_fd(cmd->arg[0], 2);
		ft_putstr_fd("== ", 2);
		ft_putnbr_fd(cmd->done, 2);
		ft_putstr_fd("\nlen == ", 2);
		ft_putnbr_fd(ft_strlen(cmd->arg[0]), 2);
		ft_putchar_fd('\n', 2);
		cmd = cmd->right;
	}
	free_cmd(head);
}

void						loop_shell(void)
{
	char					*line;
	t_21sh					*sh;
	t_cmd 					*cmd;

	line = NULL;
	if ((sh = get_21sh(NULL)) != NULL)
	{
		while (print_prompt())
		{
			if ((line = get_line_entree()) == NULL)
				break ;
			if (at_save_history(line) == true)
				if (add_history(&sh->hist, line) == ERROR)
					break ;
			put_line_entre(line);
			if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(sh->reset)) == -1)
				break ;
			if ((cmd = parse_cmd(line, NULL, 0)) != NULL)
				loop_cmd(cmd, cmd);
			if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(sh->term_param)) == -1)
				break ;
			ft_memdel((void**)&line);
		}
		del_21sh();
	}
}