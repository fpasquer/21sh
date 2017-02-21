/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:20:14 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/21 23:00:28 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../../incs/shell_21sh.h"

# define NONE 1
# define CLEAR 2
# define APPEND 4
# define NAPPEND 8
# define DELETE 16

static int			save_flag_history(int flag, char *arg)
{
	int				i;

	i = 0;
	if (arg == NULL || arg[i] != '-')
		return (ERROR);
	if (arg[i + 1] == '\0')
		return (false);
	while (arg[++i] != '\0')
	{
		if (arg[i] == 'c')
			flag = flag ^ CLEAR;
		else if (arg[i] == 'd')
			flag = flag ^ DELETE;
		else if (arg[i] == 'a')
			flag = flag ^ APPEND;
		else if (arg[i] == 'n')
			flag = flag ^ NAPPEND;
		else
			return (false);
	}
	return (flag);
}

static int			ret_flags_history(t_cmd *cmd)
{
	int				i;
	int				flag;

	if (cmd == NULL && !(ft_strcmp(cmd->arg[0], "history") == 0))
		return (ERROR);
	i = 1;
	flag = NONE;

	while (cmd->arg[i] != NULL)
		if (cmd->arg[i++][0] == '-')
			if ((flag = save_flag_history(flag, cmd->arg[i - 1])) == ERROR ||
					flag == false)
				return (flag);
	return (flag);
}

int					builtin_history(t_cmd *cmd)
{
	int				flag;

	if (cmd == NULL || (flag = ret_flags_history(cmd)) == ERROR)
		return (ERROR);
	if (flag == false)
		return (false);
	printf("LINE = %d flag = %d\n", __LINE__, flag);
	return (true);
}
