/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 08:52:20 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/14 09:20:04 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

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
	key_exit(0);
	return (true);
}
