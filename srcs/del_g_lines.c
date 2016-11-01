/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_g_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 20:08:24 by fpasquer          #+#    #+#             */
/*   Updated: 2016/11/01 10:22:47 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"

static void					loop_del_g_lines(t_line **lines)
{
	t_entry					*curs;
	t_entry					*mem;

	if (lines == NULL || *lines == NULL)
		return ;
	curs = (*lines)->line;
	while (curs != NULL)
	{
		mem = curs->next;
		ft_memdel((void**)&curs);
		curs = mem;
	}
	ft_memdel((void**)lines);
}

void						del_g_lines()
{
	t_line					*tmp;

	while (g_lines != NULL)
	{
		tmp = g_lines->next;
		loop_del_g_lines(&g_lines);
		g_lines = tmp;
	}
	g_curs = NULL;
}
