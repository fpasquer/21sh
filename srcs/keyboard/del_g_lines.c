/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_g_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:28:25 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/15 18:26:06 by fcapocci         ###   ########.fr       */
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

void						del_g_lines(void)
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
