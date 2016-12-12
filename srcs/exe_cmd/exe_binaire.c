/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2016/12/12 17:01:07 by fcapocci         ###   ########.fr       */
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
	if (cmd->pipefd[0] != -1)
	{
		close(cmd->pipefd[1]);
		dup2(cmd->pipefd[0], STDIN_FILENO);
	}
	if (cmd->op == PIP)
	{
		close(cmd->right->pipefd[0]);
		dup2(cmd->right->pipefd[1], STDOUT_FILENO);
	}
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

	ret = 1;
	if ((pid = fork()) != -1)
	{
		if (pid == 0)
			ft_execve(cmd, env, NULL);
		else
			waitpid(pid, &ret, WUNTRACED);
	}
	if (WIFEXITED(ret))
	{
		ret = WEXITSTATUS(ret);
		cmd->done = ret;
	}
	if (cmd->pipefd[0] != -1)
		close(cmd->pipefd[0]);
}

static void			ft_pipe(t_cmd **cmd, char **env)
{
	pid_t			pid;
	int				ret;

	ret = 1;
	if ((pid = fork()) != -1)
	{
		if (pid == 0)
			ft_execve(*cmd, env, NULL);
		else
			waitpid(pid, &ret, WUNTRACED);
	}
	if (WIFEXITED(ret))
	{
		ret = WEXITSTATUS(ret);
		(*cmd)->done = ret;
	}
	if ((*cmd)->pipefd[0] != -1)
		close((*cmd)->pipefd[0]);
	close((*cmd)->right->pipefd[1]);
	*cmd = (*cmd)->right;
}

int					exe_binaire(t_cmd *cmd, char **env)
{
	t_21sh			*sh;

	if (((sh = get_21sh(NULL)) == NULL) ||
			tcsetattr(0, TCSADRAIN, &(sh->reset)) == -1)
		return (false);
	while (cmd->op == PIP)
	{
		pipe(cmd->right->pipefd);
		ft_pipe(&cmd, env);
	}
	if (cmd->op != PIP && cmd->done == -1)
		other_exe(cmd, env);
	if (tcsetattr(0, TCSADRAIN, &(sh->term_param)) == -1)
		return (false);
	return (true);
}
