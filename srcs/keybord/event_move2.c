/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_move2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:34:56 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/24 16:20:40 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

int				line_up(void)
{
	t_line		*c;
	size_t		save_x;
	size_t		save_y;

	if ((c = g_curs) == NULL || c->curs == NULL || c->y_i == 0)
		return (false);
	save_x = c->x_i;
	save_y = c->y_i;
	while (c->curs && (c->y_i > (save_y - 1) || c->x_i != save_x))
		move_left();
	return (true);
}

int				line_down(void)
{
	t_line		*c;
	size_t		sv_x;
	size_t		sv_y;

	if ((c = g_curs) == NULL || c->len == 0 || c->y_i == c->y)
		return (false);
	sv_y = c->y_i;
	sv_x = c->i == ULONG_MAX ? g_lines->x_i : c->x_i;
	if (c->i == ULONG_MAX && c->y_i < (sv_y + 1))
		move_right();
	while (c->curs && c->curs->next && (c->y_i < (sv_y + 1) || c->x_i != sv_x))
		move_right();
	return (true);
}

int				word_left(void)
{
	t_line		*c;

	if ((c = g_curs) == NULL || c->curs == NULL)
		return (false);
	if (c->curs->c == ' ')
		while (c->curs && c->curs->c == ' ')
			move_left();
	else
		while (c->curs && c->curs->c != ' ')
			move_left();
	return (true);
}

int				word_right(void)
{
	t_line		*c;

	if ((c = g_curs) == NULL || c->len == 0)
		return (false);
	if (c->i == ULONG_MAX && c->len != 0)
		move_right();
	if (c->curs && c->curs->next && c->curs->next->c == ' ')
		while (c->curs && c->curs->next && c->curs->next->c == ' ')
			move_right();
	else
		while (c->curs && c->curs->next && c->curs->next->c != ' ')
			move_right();
	return (true);
}
