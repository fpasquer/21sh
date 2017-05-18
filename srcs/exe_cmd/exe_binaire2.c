/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 22:40:11 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/18 08:59:16 by fcapocci         ###   ########.fr       */
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

void				ft_execve(t_cmd *cmd, char **env, char *exe)
{
	if (redirecting(cmd->left, cmd->cmd, cmd->tgt_fd, 0) != 0)
		exit(EXIT_FAILURE);
	if (check_access(cmd, NULL) == false)
		exit(EXIT_FAILURE);
	if (get_path_bin(cmd->arg[0], &exe) && execve(exe, cmd->arg, env) == -1)
		exit_error(exe, "command not found");
	else if (execve(cmd->arg[0], cmd->arg, env) == -1)
		exit_error(cmd->arg[0], "command not found");
}
