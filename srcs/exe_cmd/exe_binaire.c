/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/04 17:39:18 by fcapocci         ###   ########.fr       */
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

static void			ft_pipe(t_cmd *cmd, char **env)
{
	int				pipefd[2];
	int				std[3];

	save_fd(std);
	if (builtin_pipe(cmd, 0, std) == false)
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
				change_pipe(pipefd, std[0], 3);
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
	t_21sh			*sh;

	if (cmd && cmd->done == -1)
	{
		env = l_l_to_arr_env(cmd->env, cmd->env_i);
	//	fprintf(debug, "\nCMD NAME =============>> %s\n\n", cmd->arg[0]);
	//	int i = 0;
	//	while (env[i])
	//		fprintf(debug, "%s\n", env[i++]);
		if (cmd->op == PIP && cmd->right)
			ft_pipe(cmd, env);
		else
			other_exe(cmd, env);
		delete_env_array(env);
		if ((sh = get_21sh(NULL)) != NULL)
			sh->last_exe = cmd->done;
	}
}
