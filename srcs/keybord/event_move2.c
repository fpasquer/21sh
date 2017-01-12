/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_move2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:34:56 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/13 00:03:10 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

/*int				line_up(void)
{
}

int				line_down(void)
{
}
*/

int				word_left(void)
{
	t_line		*c;

	if ((c = g_lines) == NULL)
		return (false);
	if (c->curs == NULL || c->curs->next == NULL)
		return (false);
	if (c->curs->next->c == 9 || c->curs->next->c == 32)
	{
		while ((c->curs && c->curs->next && c->curs->next->c == 9)
		|| (c->curs && c->curs->next && c->curs->next->c == 32))
		{
			move_left();
			c = g_lines;
		}
	}
	else
	{
		while ((c->curs && c->curs->next && c->curs->next->c != 9)
		|| (c->curs && c->curs->next && c->curs->next->c != 32))
		{
			move_left();
			c = g_lines;
		}
	}
	return (true);
}

int				word_right(void)
{
	t_line		*c;

	if ((c = g_lines) == NULL)
		return (false);
	if (c->curs == NULL || c->curs->next == NULL)
		return (false);
	if (c->curs->next->c == 9 || c->curs->next->c == 32)
	{
		while ((c->curs && c->curs->next && c->curs->next->c == 9)
		|| (c->curs && c->curs->next && c->curs->next->c == 32))
		{
			move_right();
			c = g_lines;
		}
	}
	else
	{
		while ((c->curs && c->curs->next && c->curs->next->c != 9)
		|| (c->curs && c->curs->next && c->curs->next->c != 32))
		{
			move_right();
			c = g_lines;
		}
	}
	return (true);
}
