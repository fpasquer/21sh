/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_not.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:39:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/19 08:04:15 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"
#include <signal.h>

t_builtin_lst g_builtin_lst[] = {
	{"cd", cd},
	{"env", builtin_env},
	{"setenv", builtin_setenv},
	{"unsetenv", builtin_unsetenv},
	{"history", builtin_history},
	{"echo", builtin_echo},
	{"exit", builtin_exit},
	{NULL, NULL},
};

static void		builtin_pipe_manager(int s_fd, int pipefd[2], t_cmd *c)
{
	change_pipe(pipefd, 0, 1);
	change_pipe(pipefd, 0, 2);
	exe_binaire(c->right);
	dup2(STDIN_FILENO, s_fd);
	dup2(STDOUT_FILENO, 1);
}

int				builtin_pipe(t_cmd *content, int i, int pipefd[2], int s_fd)
{
	if (content->arg && len_y(content->arg) > 0)
	{
		while (g_builtin_lst[i].str)
		{
			if (ft_strequ(content->arg[0], g_builtin_lst[i].str))
			{
				redirecting(content->left, content->cmd, content->tgt_fd, 0);
				content->done = g_builtin_lst[i].p(content) == true ? 0 : 1;
				builtin_pipe_manager(s_fd, pipefd, content);
				return (true);
			}
			i++;
		}
	}
	return (false);
}

int				builtin_or_not(t_cmd *content, int i)
{
	int			save_in;
	int			save_out;

	if (content->arg && len_y(content->arg) > 0)
	{
		while (g_builtin_lst[i].str)
		{
			if (ft_strequ(content->arg[0], g_builtin_lst[i].str))
			{
				save_in = dup(STDIN_FILENO);
				save_out = dup(STDOUT_FILENO);
				redirecting(content->left, content->cmd, content->tgt_fd, 0);
				content->done = g_builtin_lst[i].p(content) == true ? 0 : 1;
				dup2(save_in, STDIN_FILENO);
				dup2(save_out, STDOUT_FILENO);
				return (true);
			}
			i++;
		}
	}
	return (false);
}
