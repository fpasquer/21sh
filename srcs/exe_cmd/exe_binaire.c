/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/08 16:46:47 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

static void			change_pipe(int pipefd[2], int save_fd, int choice)
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
}

static void			other_exe(t_cmd *cmd, char **env)
{
	pid_t			pid;
	int				ret;

	ret = 1;
	if (builtin_or_not(cmd, 0) == false)
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

static void			ft_pipe(t_cmd *cmd, char **env)
{
	pid_t			pid;
	int				ret;
	int				pipefd[2];
	int				save_fd;

	save_fd = dup(STDIN_FILENO);
	ret = 1;
	pipe(pipefd);
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
			if (cmd->right)
				exe_binaire(cmd->right, env);
			change_pipe(pipefd, save_fd, 3);
		}
		waitpid(pid, &ret, WUNTRACED | WNOHANG);
	}
	cmd->done = WIFEXITED(ret) ? WEXITSTATUS(ret) : 0;
}

void				exe_binaire(t_cmd *cmd, char **env)
{
	if (cmd->op == PIP)
		ft_pipe(cmd, env);
	else
		other_exe(cmd, env);
}
