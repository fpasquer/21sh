/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 22:56:29 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/11 01:47:50 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"

int					take_cmd_if_exist(char **tmp_line, char **tab)
{
	int				ret;
	t_cmd			*cmd;

	ret = tab_env_i(tmp_line, &tab);
	if ((cmd = parse_cmd(*tmp_line, NULL, 0)) != NULL)
	{
		other_exe(cmd, tab);
		free_cmd(cmd);
	}
	return (ret);
}
