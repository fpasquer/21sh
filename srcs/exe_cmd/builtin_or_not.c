/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_or_not.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:18:15 by jchen             #+#    #+#             */
/*   Updated: 2016/10/14 08:51:29 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

t_builtin_lst g_builtin_lst[] = {
	{"cd", cd},
	{"env", builtin_env},
	{"setenv", builtin_setenv},
	{"exit", builtin_exit},
	{NULL, NULL},
};

void		builtin_or_not(t_cmd *content) {
	int 	i;

	i = 0;
	if (content->argc > 0) {
		while (g_builtin_lst[i].str) {
			if (ft_strequ(content->arg[0], g_builtin_lst[i].str)) {
				g_builtin_lst[i].p(content);
				break ;
			}
			i++;
		}
	}
}
