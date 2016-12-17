/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_not.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:18:15 by jchen             #+#    #+#             */
/*   Updated: 2016/12/17 19:05:39 by fcapocci         ###   ########.fr       */
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
				g_builtin_lst[i].p(content);
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
