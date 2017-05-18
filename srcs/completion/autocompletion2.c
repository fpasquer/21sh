/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 11:55:30 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/18 11:59:10 by fpasquer         ###   ########.fr       */
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
