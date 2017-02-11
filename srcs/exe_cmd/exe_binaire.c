/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/10 19:24:18 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

void				change_pipe(int pipefd[2], int save_fd, int choice)
{
	if (choice == 1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
	}
	else if (choice == 2)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
	}
	else if (choice == 3)
	{
		dup2(save_fd, STDIN_FILENO);
		close(pipefd[0]);
	}
	else if (choice == 4)
	{
		dup2(save_fd, STDOUT_FILENO);
		close(pipefd[1]);
	}
}

void				other_exe(t_cmd *cmd, char **env)
{
	pid_t			pid;
	int				ret;

	ret = 1;
	if (builtin_or_not(cmd, 0, NULL, 0) == false)
	{
		if ((pid = fork()) != -1)
		{
			if (pid == 0)
				ft_execve(cmd, env, NULL);
		}
		waitpid(pid, &ret, WUNTRACED);
		if (WIFEXITED(ret))
			cmd->done = WEXITSTATUS(ret);
	}
}

static void			ft_pipe(t_cmd *cmd, char **env, int ret)
{
	pid_t			pid;
	int				pipefd[2];
	int				save_fd;

	save_fd = dup(STDIN_FILENO);
	pipe(pipefd);
	if (builtin_or_not(cmd, 0, pipefd, save_fd) == false)
	{
		if ((pid = fork()) != -1)
		{
			if (pid == 0)
			{
				change_pipe(pipefd, 0, 1);
				ft_execve(cmd, env, NULL);
			}
			else
			{
				change_pipe(pipefd, 0, 2);
				exe_binaire(cmd->right);
				change_pipe(pipefd, save_fd, 3);
			}
			waitpid(pid, &ret, WUNTRACED | WNOHANG);
		}
		cmd->done = WIFEXITED(ret) ? WEXITSTATUS(ret) : 0;
	}
}

void				exe_binaire(t_cmd *cmd)
{
	char			**env;

	env = l_l_to_arr_env();
	if (cmd->op == PIP && cmd->right)
		ft_pipe(cmd, env, 1);
	else
		other_exe(cmd, env);
	delete_env_array(env);
}
