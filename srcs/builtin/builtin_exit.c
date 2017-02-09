/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:52:22 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/08 22:15:44 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							builtin_exit(t_cmd *cmd)
{
	int						val;

	if (cmd != NULL && cmd->arg[0] != NULL &&
			ft_strcmp(cmd->arg[0], "exit") == 0 &&
				cmd->arg[1] != NULL && ft_is_number(cmd->arg[1]) == true)
	{
		val = ft_atoi(cmd->arg[1]);
		key_exit((unsigned char)val);
	}
	key_exit(EXIT_SUCCESS);
	return (true);
}
