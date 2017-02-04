/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:07:29 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/04 17:04:22 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							modify_env_value(char *name, char *value)
{
	t_env					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (false);
	curs = sh->env;
	while (curs != NULL)
	{
		if (curs->name && ft_strcmp(name, curs->name) == 0)
		{
			ft_memdel((void**)&(curs->value));
			if ((curs->value = value ? ft_strdup(value)
				: ft_strdup("")) == NULL)
				return (false);
			return (true);
		}
		curs = curs->next;
	}
	return (false);
}
