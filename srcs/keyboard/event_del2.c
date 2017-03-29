/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_del2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:00:38 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/29 20:18:53 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static int			save_info_line(t_line **line)
{
	t_21sh			*sh;

	if (line == NULL || *line == NULL || (sh = get_21sh(NULL)) == NULL)
		return (false);
	(*line)->len--;
	if (save_y_x_line(line) == ERROR)
		return (ERROR);
	return (put_cmd());
}

static int			del_right_line(t_line *c, t_entry *tmp)
{
	if (place_curs() == ERROR)
		return (ERROR);
	if (tmp == NULL)
	{
		tmp = c->curs->next;
		if (c->curs->next->next)
			c->curs->next->next->prev = c->curs;
		c->curs->next = c->curs->next->next ?
			c->curs->next->next : NULL;
	}
	else
	{
		tmp = c->line;
		if (c->line->next)
			c->line->next->prev = NULL;
		c->line = c->line->next;
	}
	if (save_info_line(&c) == ERROR)
		return (ERROR);
	ft_memdel((void**)&tmp);
	return (true);
}

int					del_right(void)
{
	t_line			*c;

	if ((c = g_curs) == NULL)
		return (false);
	if (c->curs && c->curs->next)
		return (del_right_line(c, NULL));
	else if (c->curs == NULL && c->line)
		return (del_right_line(c, c->line));
	return (false);
}

int					del_selec(void)
{
	t_line			*c;

	if ((c = g_curs) == NULL || c->line == NULL || c->len == 0)
		return (reset_selec(false));
	if (c->lft_rgt >= 0)
	{
		move_right();
		while (c->curs && c->curs->select == 1)
			del_left();
		return (reset_selec(true));
	}
	else
	{
		while (c->curs ? c->curs->next && c->curs->next->next
			&& c->curs->next->next->select == 1 : c->line && c->line->next
				&& c->line->next->select == 1)
			del_right();
		if (c->curs || (!c->curs && c->line))
		{
			move_right();
			del_left();
		}
		return (reset_selec(true));
	}
	return (reset_selec(false));
}
