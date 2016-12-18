/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2016/12/18 23:36:53 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

static void			exit_error(char *cmd, char *error)
{
	ft_putstr_fd("error", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
	}
	if (error)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static int			check_access(t_cmd *cmd, char *cpy)
{
	int				i;

	i = access(cmd->arg[0], X_OK);
	if (i == ERROR && get_path_bin(cmd->arg[0], &cpy) == 0)
	{
		ft_putstr_fd("error: ", STDERR_FILENO);
		ft_putstr_fd(cmd->arg[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if ((cmd->arg[0][0] == '.' && cmd->arg[0][1] && cmd->arg[0][1] == '/')
				|| cmd->arg[0][0] == '/')
			ft_putendl_fd("no such file or directory", STDERR_FILENO);
		else
			ft_putendl_fd("command not found", STDERR_FILENO);
		return (false);
	}
	return (true);
}

static void			ft_execve(t_cmd *cmd, char **env, char *exe)
{
	redirecting(cmd->left, cmd->cmd, cmd->tgt_fd, 0);
	if (check_access(cmd, NULL) == false)
		exit(EXIT_FAILURE);
	if (get_path_bin(cmd->arg[0], &exe) && execve(exe, cmd->arg, env) == -1)
		exit_error(exe, "command not found");
	else if (execve(cmd->arg[0], cmd->arg, env) == -1)
		exit_error(cmd->arg[0], "command not found");
}

static void			other_exe(t_cmd *cmd, char **env)
{
	pid_t			pid;
	int				ret;

	ft_putendl_fd("OTHER_EXE", 2);
	ret = 1;
	if ((pid = fork()) != -1)
	{
		if (pid == 0)
			ft_execve(cmd, env, NULL);
	}
	waitpid(pid, &ret, WUNTRACED);
	if (WIFEXITED(ret))
		cmd->done = WEXITSTATUS(ret);
}

static void			change_pipe(int pipefd[2], int choice)
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
}

static void			ft_pipe(t_cmd *cmd, char **env)
{
	pid_t			pid;
	int				ret;
	int				pipefd[2];

	ft_putendl_fd("FT_PIPE", 2);
	ret = 1;
	pipe(pipefd);
	if ((pid = fork()) != -1)
	{
		if (pid == 0)
		{
			change_pipe(pipefd, 1);
			ft_execve(cmd, env, NULL);
		}
		else
		{
			change_pipe(pipefd, 2);
			if (cmd->right)
				exe_binaire(cmd->right, env);
		}
	}
	waitpid(pid, &ret, WUNTRACED | WNOHANG);
	cmd->done = WIFEXITED(ret) ?  WEXITSTATUS(ret) : 0;
}

void				exe_binaire(t_cmd *cmd, char **env)
{
	if (cmd->op == PIP)
		ft_pipe(cmd, env);
	else
		other_exe(cmd, env);
}
