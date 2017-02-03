/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_selec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:12:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/03 21:06:47 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

int					reset_selec(int ret)
{
	t_line			*curs;
	t_entry			*cpy;

	if ((curs = g_curs) == NULL || curs->activity == false)
		return (false);
	if ((cpy = curs->line) != NULL)
	{
		while (cpy)
		{
			cpy->select = false;
			cpy = cpy->next;
		}
	}
	curs->sel_start = NULL;
	curs->sel_end = NULL;
	curs->activity = false;
	curs->lft_rgt = 0;
	curs->last_dir = 0;
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
	{
		curs->sel_start = NULL;
		curs->activity = true;
	}
	return (true);
}

int					selec_manager(size_t l_r)
{
	t_line			*c;

	if ((c = g_curs) == NULL || c->len == 0 || c->activity == false)
		return (false);
	c->last_dir = c->last_dir == 0 ? l_r : c->last_dir;
	if (c->sel_start == NULL && c->curs == NULL)
		c->sel_start = c->line;
	else if (c->sel_start == NULL && c->curs)
		c->sel_start = c->curs->next ? c->curs->next : c->curs;
	if (c->curs && c->curs->next && c->lft_rgt == 0)
		c->curs->next->select = true;
	else if (c->curs && c->curs->next && c->last_dir == l_r)
		c->curs->next->select = c->activity == true
			&& c->curs->next->select == 0 ? 1 : 0;
	else if (c->curs == NULL && c->line && c->last_dir == l_r)
		c->line->select = c->activity == 1 && c->line->select == 0 ? 1 : 0;
	if (l_r == 1 && c->line)
		c->sel_end = c->curs ? c->curs : c->line;
	else if (l_r == 2 && c->curs && c->curs->next)
		c->sel_end = c->curs->next->next ? c->curs->next->next : c->curs->next;
	else if (l_r == 2 && c->curs && c->curs->next == NULL)
		c->sel_end = c->curs;
	c->lft_rgt = l_r == 1 ? (c->lft_rgt - 1) : (c->lft_rgt + 1);
	c->last_dir = l_r;
	return (true);
}
