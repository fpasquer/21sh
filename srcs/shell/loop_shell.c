/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:29:13 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 16:54:35 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>

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

static void					loop_cmd(t_cmd *cmd, t_cmd *head, t_21sh *sh)
{
	while (cmd && cmd->arg && cmd->arg[0] != NULL)
	{
	//	fprintf(debug, "\n\nexe la cmd %s\n\n", cmd->arg[0]);
		exe_binaire(cmd);
		while ((cmd->right && cmd->op == PIP && cmd->done >= 0
				&& cmd->right->done != -1)
				|| (cmd->right && cmd->op == ET && sh->last_exe > 0)
				|| (cmd->right && cmd->op == OU && sh->last_exe == 0))
		{
	//		ft_putendl_fd("SKIP_CMD", 2);
	//		ft_putstr_fd("cmd->", 2);
	//		ft_putstr_fd(cmd->arg[0], 2);
	//		ft_putstr_fd("== ", 2);
	//		ft_putnbr_fd(cmd->done, 2);
	//		ft_putstr_fd("   last_exe == ", 2);
	//		ft_putnbr_fd(sh->last_exe, 2);
	//		ft_putstr_fd("\nlen == ", 2);
	//		ft_putnbr_fd(ft_strlen(cmd->arg[0]), 2);
	//		ft_putchar_fd('\n', 2);
			cmd = cmd->right;
		}
	//	ft_putstr_fd("cmd->", 2);
	//	ft_putstr_fd(cmd->arg[0], 2);
	//	ft_putstr_fd("== ", 2);
	//	ft_putnbr_fd(cmd->done, 2);
	//	ft_putstr_fd("   last_exe == ", 2);
	//	ft_putnbr_fd(sh->last_exe, 2);
	//	ft_putstr_fd("\nlen == ", 2);
	//	ft_putnbr_fd(ft_strlen(cmd->arg[0]), 2);
	//	ft_putchar_fd('\n', 2);
		cmd = cmd->right;
	}
	free_cmd(head);
}

void						loop_shell(void)
{
	char					*line;
	t_21sh					*sh;
	t_cmd					*cmd;

	line = NULL;
	if ((sh = get_21sh(NULL)) != NULL)
	{
		while (print_prompt())
		{
			if ((line = get_line_entree(false)) == NULL)
				break ;
			if (at_save_history(line) == true)
				if (add_history(&sh->hist, line) == ERROR)
					break ;
			if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(sh->reset)) == -1)
				break ;
			if ((cmd = parse_cmd(line, NULL, 0)) != NULL)
				loop_cmd(cmd, cmd, sh);
			if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(sh->term_param)) == -1)
				break ;
			ft_memdel((void**)&line);
		}
		del_21sh();
	}
}
