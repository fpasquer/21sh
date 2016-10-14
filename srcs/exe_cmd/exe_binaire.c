/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/14 16:10:59 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

int					exe_binaire(t_cmd *cmd, char **env)
{
	char			*exe;
	t_21sh			*sh;
	pid_t			pid;

	if ((sh = get_21sh(NULL)) && get_path_bin(cmd->arg[0], &exe))
	{
		pid = fork();
		if (pid < 0)
			return (false);
		if (pid == 0)
		{
			if (execve(exe, cmd->arg, env) == -1)
				return (false);	//ameliorer en cas de fork qui ne ferme pas
		}
		else
			wait(&pid);
		return (true);
	}
	return (false);
}
