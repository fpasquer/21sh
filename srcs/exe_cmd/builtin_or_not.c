/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_not.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:39:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/08 10:49:32 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

t_builtin_lst g_builtin_lst[] = {
	{"cd", cd},
	{"env", builtin_env},
	{"setenv", builtin_setenv},
	{"unsetenv", builtin_unsetenv},
	{"exit", builtin_exit},
	{NULL, NULL},
};

void			builtin_or_not(t_cmd *content, int i, int builtin)
{
	char		**env;

	env = NULL;
	if (content->arg && len_y(content->arg) > 0)
	{
		while (g_builtin_lst[i].str)
		{
			if (ft_strequ(content->arg[0], g_builtin_lst[i].str))
			{
				if (g_builtin_lst[i].p(content) == true)
					content->done = 0;
				else
					content->done = 1;
				builtin = 1;
				break ;
			}
			i++;
		}
		if (!builtin)
		{
			env = l_l_to_arr_env();
			exe_binaire(content, env);
			delete_env_array(env);
		}
	}
}
