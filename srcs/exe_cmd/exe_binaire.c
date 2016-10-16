/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/16 17:23:34 by jchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"


static void			exit_error(char *cmd, char *error)
{
	ft_putstr_fd("error", 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (error)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error, 2);
	}
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

static void			check_cmd(t_cmd *cmd, char **env)
{
	char			*exe;

	if (get_path_bin(cmd->arg[0], &exe) &&
			execve(exe, cmd->arg, env) == -1)
	{
		ft_putendl("PASS3"); //debug
		exit_error(exe, "command not found");
	}
	else if (execve(cmd->arg[0], cmd->arg, env) == -1)
	{
		ft_putendl("PASS4"); //debug
		exit_error(cmd->arg[0], "command not found");
	}
}

int					exe_binaire(t_cmd *cmd, char **env)
{
	pid_t			pid;
	t_21sh			*sh;
	int				ret;

	ret = 0;
	if (((sh = get_21sh(NULL)) == NULL) ||
			tcsetattr(0, TCSADRAIN, &(sh->reset)) == -1)
		return (false);
	if ((pid = fork()) != -1)
	{
		if (pid == 0)
		{
			ft_putendl("FILS");
			check_cmd(cmd, env);
		}
		else
		{
			waitpid(pid, &ret, WUNTRACED);
			ft_putendl("PERE");
		}
	}
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	if (tcsetattr(0, TCSADRAIN, &(sh->term_param)) == -1)
		return (false);
	return (true);
}
