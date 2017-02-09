/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_not.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:39:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/09 18:28:38 by fcapocci         ###   ########.fr       */
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
	{"exit", builtin_exit},
	{NULL, NULL},
};

static void		builtin_pipe_manager(int pipefd[2], int sav, int s_fd, t_cmd *c)
{
	if (pipefd != NULL)
	{
		change_pipe(pipefd, sav, 4);
		dup2(pipefd[0], STDIN_FILENO);
		exe_binaire(c->right);
		change_pipe(pipefd, s_fd, 3);
	}
}

int				builtin_or_not(t_cmd *content, int i, int pipefd[2], int s_fd)
{
	int			save;

	if (content->arg && len_y(content->arg) > 0)
	{
		while (g_builtin_lst[i].str)
		{
			if (ft_strequ(content->arg[0], g_builtin_lst[i].str))
			{
				save = dup(STDOUT_FILENO);
				if (pipefd != NULL)
					dup2(pipefd[1], STDOUT_FILENO);
				redirecting(content->left, content->cmd, content->tgt_fd, 0);
				content->done = g_builtin_lst[i].p(content) == true ? 0 : 1;
				builtin_pipe_manager(pipefd, save, s_fd, content);
				return (true);
			}
			i++;
		}
	}
	return (false);
}
