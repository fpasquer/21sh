/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_selec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:12:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/23 17:28:28 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

static bool			reset_selec(bool ret)
{
	t_line			*curs;
	t_entry			*cpy;

	if ((curs = g_curs) == NULL)
		return (false);
	cpy = curs->curs;
	while (cpy)
	{
		cpy->select = false;
		cpy = cpy->next;
	}
	curs->activity = false;
	return (ret);
}

int					selec_mode(void)
{
	t_line			*curs;

	if ((curs = g_curs) == NULL)
		return (false);
	if (curs->activity == true)
		reset_selec(true);
	else
		curs->activity = true;
	return (true);
}

void				selec_manager(void)
{
}
