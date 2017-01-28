/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_selec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:12:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/28 18:06:46 by fcapocci         ###   ########.fr       */
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
	cpy = curs->line;
	while (cpy)
	{
		cpy->select = false;
		cpy = cpy->next;
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
	if (c->curs && c->curs->next && c->lft_rgt == 0)
		c->curs->next->select = true;
	else if (c->curs && c->curs->next && c->last_dir == l_r)
		c->curs->next->select = c->activity == true
			&& c->curs->next->select == 0 ? 1 : 0;
	else if (c->curs == NULL && c->line && c->last_dir == l_r)
		c->line->select = c->activity == 1 && c->line->select == 0 ? 1 : 0;
	if (l_r == 1 && c->curs)
		c->sel_end = c->curs;
	else if (l_r == 2 && c->curs && c->curs->next)
		c->sel_end = c->curs->next->next ? c->curs->next->next : c->curs->next;
	else
		c->sel_end = c->line;
	c->lft_rgt = l_r == 1 ? (c->lft_rgt - 1) : (c->lft_rgt + 1);
	c->last_dir = l_r;
	return (true);
}

static int			del_curs(t_line *orig, t_entry *c)
{
	if (orig == NULL || c == NULL)
		return (false);

	return (true);
}

int					del_selec(void)
{
	t_entry			*c;

	if (g_curs == NULL || (c = g_curs->line) == NULL)
		return (false);
	if (g_curs->curs && g_curs->curs->next)
		g_curs->curs->next->select = true;
	else if (g_curs->curs && g_curs->curs->next == NULL)
		g_curs->curs->select = true;
	else
		c->select = true;
	while (c)
	{
		if (c->select == true)
			if (del_curs(g_curs, c) == false)
				return (false);
		c = c->next;
	}
	return (true);
}
