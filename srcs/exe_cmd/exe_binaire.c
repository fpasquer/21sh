/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binaire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:22:59 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/22 15:12:19 by fcapocci         ###   ########.fr       */
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

static void			check_cmd(t_cmd *cmd, char **env, char *exe)
{
	if (get_path_bin(cmd->arg[0], &exe) && execve(exe, cmd->arg, env) == -1)
		exit_error(exe, "command not found");
	else if (execve(cmd->arg[0], cmd->arg, env) == -1)
		exit_error(cmd->arg[0], "command not found");
}

static int			check_access(t_cmd *cmd, char *cpy, int *ret)
{
	int				i;

	i = access(cmd->arg[0], X_OK);
	if (i == ERROR && get_path_bin(cmd->arg[0], &cpy) == 0)
	{
		*ret = 1;
		cmd->done = *ret;
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(cmd->arg[0], 2);
		ft_putstr_fd(": ", 2);
		if ((cmd->arg[0][0] == '.' && cmd->arg[0][1] && cmd->arg[0][1] == '/')
				|| cmd->arg[0][0] == '/')
			ft_putendl_fd("no such file or directory", 2);
		else
			ft_putendl_fd("command not found", 2);
		return (false);
	}
	return (true);
}

int					exe_binaire(t_cmd *cmd, char **env)
{
	pid_t			pid;
	t_21sh			*sh;
	int				ret;
	char			*exe;

	ret = 0;
	if (check_access(cmd, NULL, &ret) == false)
		return (false);
	if (((sh = get_21sh(NULL)) == NULL) ||
			tcsetattr(0, TCSADRAIN, &(sh->reset)) == -1)
		return (false);
	if ((pid = fork()) != -1)
	{
		if (pid == 0)
			check_cmd(cmd, env, exe);
		else
			waitpid(pid, &ret, WUNTRACED);
	}
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	cmd->done = ret;
	if (tcsetattr(0, TCSADRAIN, &(sh->term_param)) == -1)
		return (false);
	return (true);
}
