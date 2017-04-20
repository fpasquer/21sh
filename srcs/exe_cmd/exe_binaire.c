/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/20 06:38:51 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"
#include <signal.h>

void				other_exe(t_cmd *cmd, char **env)
{
	if (builtin_or_not(cmd, 0) == false)
	{
		if ((cmd->pid = fork()) != -1)
		{
			if (cmd->pid == 0)
				ft_execve(cmd, env, NULL);
			waitpid(cmd->pid, &cmd->status, WUNTRACED);
		}
		cmd->done = WIFEXITED(cmd->status) ? WEXITSTATUS(cmd->status) : 130;
	}
}

static void			ft_pipe(t_cmd *cmd, char **env, int save_in, int save_out)
{
	int				pipefd[2];

	save_fd(&save_in, &save_out);
	if (builtin_pipe(cmd, 0, save_in, save_out) == false)
	{
		pipe(pipefd);
		if ((cmd->pid = fork()) != -1)
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
				change_pipe(pipefd, save_in, 3);
				waitpid(cmd->right->pid, &cmd->right->status, WUNTRACED);
				kill(cmd->pid, 2);
			}
			waitpid(cmd->pid, &cmd->status, WUNTRACED);
		}
		cmd->done = WIFEXITED(cmd->status) ? WEXITSTATUS(cmd->status) : 130;
	}
}

void				exe_binaire(t_cmd *cmd)
{
	char			**env;

	if (cmd && cmd->done == -1)
	{
		env = l_l_to_arr_env(cmd->env, cmd->env_i);
		fprintf(debug, "\nCMD NAME =============>> %s\n\n", cmd->arg[0]);
		int i = 0;
		while (env[i])
			fprintf(debug, "%s\n", env[i++]);
		if (cmd->op == PIP && cmd->right)
			ft_pipe(cmd, env, 0, 0);
		else
			other_exe(cmd, env);
		delete_env_array(env);
	}
}
