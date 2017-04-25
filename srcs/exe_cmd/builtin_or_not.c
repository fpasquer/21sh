/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_not.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:39:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/26 00:19:25 by fcapocci         ###   ########.fr       */
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

static void		builtin_pipe_manager(int s_in, int s_out, t_cmd *c)
{
	exe_binaire(c->right);
	reset_fd(s_in, s_out);
}

int				builtin_pipe(t_cmd *content, int i, int s_in, int s_out)
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
				dup2(s_out, STDOUT_FILENO);
				change_pipe(pipefd, 0, 2);
				builtin_pipe_manager(s_in, s_out, content);
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
				save_fd(&save_in, &save_out);
				redirecting(content->left, content->cmd, content->tgt_fd, 0);
				content->done = g_builtin_lst[i].p(content) == true ? 0 : 1;
				reset_fd(save_in, save_out);
				return (true);
			}
			i++;
		}
	}
	return (false);
}
