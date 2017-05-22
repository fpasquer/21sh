/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/22 12:58:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"
#include <signal.h>

static void			other_exe(t_cmd *c, char **env)
{
	int				std[3];

	save_fd(std);
	if (builtin_or_not(c, 0, std) == false)
	{
		if ((c->pid = fork()) != -1)
		{
			if (c->pid == 0)
				ft_execve(c, env, NULL);
			waitpid(c->pid, &c->status, WUNTRACED);
		}
		c->done = WIFEXITED(c->status) ? WEXITSTATUS(c->status) : 130;
		c->done = WIFSIGNALED(c->status) ? WTERMSIG(c->status) : c->done;
	}
}

static void			ft_pipe(t_cmd *c, char **env)
{
	int				pipefd[2];
	int				std[3];

	save_fd(std);
	if (builtin_pipe(c, 0, std) == false)
	{
		if (pipe(pipefd) == 0 && (c->pid = fork()) != -1)
		{
			if (c->pid == 0)
			{
				change_pipe(pipefd, 0, 1);
				ft_execve(c, env, NULL);
			}
			else
			{
				change_pipe(pipefd, 0, 2);
				exe_binaire(c->right);
				change_pipe(pipefd, std[0], 3);
			}
			waitpid(c->pid, &c->status, WUNTRACED);
		}
		c->done = WIFEXITED(c->status) ? WEXITSTATUS(c->status) : 130;
		c->done = WIFSIGNALED(c->status) ? WTERMSIG(c->status) : c->done;
	}
}

void				exe_binaire(t_cmd *c)
{
	char			**env;
	t_21sh			*sh;

	if (c && c->done == -1)
	{
		env = l_l_to_arr_env(c->env, c->env_i);
		if (c->op == PIP && c->right)
			ft_pipe(c, env);
		else
		{
			other_exe(c, env);
			if ((sh = get_21sh(NULL)) != NULL)
				sh->last_exe = c->done;
		}
		delete_env_array(env);
	}
}
