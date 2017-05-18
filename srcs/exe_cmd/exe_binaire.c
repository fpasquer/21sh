/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/18 09:41:56 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"
#include <signal.h>

static int			heredoc_checker(t_cmd *c, int fd[2], char *buff)
{
	if ((buff = give_heredoc(c->left, c->cmd)) != NULL)
	{
		if (c->left && c->left->arg)
		{
			pipe(fd);
			ft_memdel((void**)&c->left->arg[0]);
			c->left->arg[0] = ft_strdup(buff);
			ft_memdel((void**)&buff);
			return (0);
		}
	}
	return (1);
}

static void			other_exe(t_cmd *cmd, char **env, int ret)
{
	int				pipefd[2];
	int				std[3];

	save_fd(std);
	if (builtin_or_not(cmd, 0, std) == false)
	{
		ret = heredoc_checker(cmd, pipefd, NULL);
		if ((cmd->pid = fork()) != -1)
		{
			if (cmd->pid == 0)
			{
				if (ret == 0)
					change_pipe(pipefd, 0, 2);
				ft_execve(cmd, env, NULL);
			}
			else
			{
				fprintf(debug, "ret == %d\n", ret);
				if (ret == 0)
				{
					close(pipefd[0]);
					ft_putstr_fd(cmd->left->arg[0], pipefd[1]);
					close(pipefd[1]);
				}
					//add_heredoc();
			}
			waitpid(cmd->pid, &cmd->status, WUNTRACED);
		}
		cmd->done = WIFEXITED(cmd->status) ? WEXITSTATUS(cmd->status) : 130;
		cmd->done = WIFSIGNALED(cmd->status) ? WTERMSIG(cmd->status) : cmd->done;
	}
}

static void			ft_pipe(t_cmd *cmd, char **env)
{
	int				pipefd[2];
	int				std[3];

	save_fd(std);
	if (builtin_pipe(cmd, 0, std) == false)
	{
		if (pipe(pipefd) == 0 && (cmd->pid = fork()) != -1)
		{
			if (cmd->pid == 0)
			{
				change_pipe(pipefd, 0, 1);
				ft_execve(cmd, env, NULL);
			}
			else
			{
				change_pipe(pipefd, 0, 2);
				exe_binaire(cmd->right);
				change_pipe(pipefd, std[0], 3);
			}
			waitpid(cmd->pid, &cmd->status, WUNTRACED);
		}
		cmd->done = WIFEXITED(cmd->status) ? WEXITSTATUS(cmd->status) : 130;
		cmd->done = WIFSIGNALED(cmd->status) ? WTERMSIG(cmd->status) : cmd->done;
	}
}

void				exe_binaire(t_cmd *cmd)
{
	char			**env;
	t_21sh			*sh;

	if (cmd && cmd->done == -1)
	{
		env = l_l_to_arr_env(cmd->env, cmd->env_i);
		if (cmd->op == PIP && cmd->right)
			ft_pipe(cmd, env);
		else
		{
			other_exe(cmd, env, 1);
			if ((sh = get_21sh(NULL)) != NULL)
				sh->last_exe = cmd->done;
		}
		delete_env_array(env);
	}
}
