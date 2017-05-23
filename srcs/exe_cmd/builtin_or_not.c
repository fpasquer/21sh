/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_not.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:39:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/23 16:39:31 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

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

static void		builtin_pipe_manager(int std[3], t_cmd *c)
{
	exe_binaire(c->right);
	reset_fd(std);
}

int				builtin_pipe(t_cmd *content, int i, int std[3])
{
	int			pipefd[2];

	if (content->arg && len_y(content->arg) > 0)
	{
		while (g_builtin_lst[i].str)
		{
			if (ft_strequ(content->arg[0], g_builtin_lst[i].str))
			{
				pipe(pipefd);
				dup2(pipefd[1], STDOUT_FILENO);
				redirecting(content->left, content->cmd, content->tgt_fd, 0);
				content->done = g_builtin_lst[i].p(content) == true ? 0 : 1;
				dup2(std[1], STDOUT_FILENO);
				dup2(std[2], STDERR_FILENO);
				change_pipe(pipefd, 0, 2);
				builtin_pipe_manager(std, content);
				return (true);
			}
			i++;
		}
	}
	return (false);
}

int				builtin_or_not(t_cmd *content, int i, int std[3])
{
	if (content->arg && len_y(content->arg) > 0)
	{
		while (g_builtin_lst[i].str)
		{
			if (ft_strequ(content->arg[0], g_builtin_lst[i].str))
			{
				redirecting(content->left, content->cmd, content->tgt_fd, 0);
				content->done = g_builtin_lst[i].p(content) == true ? 0 : 1;
				reset_fd(std);
				return (true);
			}
			i++;
		}
	}
	return (false);
}
