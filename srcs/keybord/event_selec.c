/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_selec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:12:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/24 16:26:06 by fcapocci         ###   ########.fr       */
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
	cpy = curs->line;
	while (cpy)
	{
		cpy->select = false;
		cpy = cpy->next;
	}
	if (curs->cp_mode == false)
	{
		curs->sel_start = NULL;
		curs->sel_end = NULL;
	}
	curs->activity = false;
	curs->last_dir = 0;
	return (ret);
}

int					selec_mode(void)
{
	t_line			*curs;

	if ((curs = g_curs) == NULL)
		return (false);
	if (curs->activity == true)
	{
		if (curs->sel_start && curs->sel_end)
		{
			fprintf(debug, "sel_start == %c sel_end == %c line cpy == ", curs->sel_start->c, curs->sel_end->c);
			while (curs->sel_start != curs->sel_end)
			{
				fprintf(debug, "%c", curs->sel_start->c);
				curs->sel_start = curs->sel_start->prev && curs->sel_start->prev->select == true ? curs->sel_start->prev : curs->sel_start->next;
			}
			fprintf(debug, "%c\n", curs->sel_start->c);
		}
		reset_selec(true);
	}
	else
		curs->activity = true;
	return (true);
}

int					selec_manager(size_t l_r)
{
	t_line			*c;

	if ((c = g_curs) == NULL || c->len == 0 || c->activity == false)
		return (false);
	if (c->last_dir == 0)
	{
		c->last_dir = l_r;
		c->sel_start = c->curs == NULL ? c->line : c->curs->next;
	}
	if (c->curs && c->curs->next && c->last_dir == l_r)
		c->curs->next->select = c->activity == true
			&& c->curs->next->select == false ? true : false;
	else if (c->curs == NULL && c->line && c->last_dir == l_r)
		c->line->select = c->activity == true
			&& c->line->select == false ? true : false;
	if (l_r == 2)
		c->sel_end = c->curs && c->curs->next ? c->curs->next : c->line;
	else
		c->sel_end = c->curs ? c->curs : c->line;
	c->last_dir = l_r;
	return (true);
}
