/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 19:25:00 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:25:15 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							del_car_begin_in_g_line(size_t len)
{
	if (g_curs == NULL)
		return (ERROR);
	if (len == 0)
		return (false);
	g_curs->curs = g_curs->line;
	while (g_curs->curs != NULL && g_curs->curs->next != NULL)
		g_curs->curs = g_curs->curs->next;
	while (g_curs->curs != NULL && g_curs->curs->c == ' ')
		del_left();
	del_left();
	len--;
	while (len > 0)
	{
		del_left();
		len--;
	}
	return (true);
}
