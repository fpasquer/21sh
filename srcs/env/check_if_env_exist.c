/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_env_exist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:07:55 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/25 20:45:47 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							check_if_env_exist(char *name, t_env *sub_env)
{
	t_env					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	curs = sub_env ? sub_env : sh->env;
	while (curs != NULL)
	{
		if (ft_strcmp(name, curs->name) == 0)
		{
			curs->add = false;
			return (true);
		}
		curs = curs->next;
	}
	return (false);
}
