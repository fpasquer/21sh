/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_move2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:34:56 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/13 19:48:33 by fcapocci         ###   ########.fr       */
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

	if ((c = g_curs) == NULL)
		return (false);
	if (c->curs == NULL || c->curs == NULL)
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

	if ((c = g_curs) == NULL)
		return (false);
	if (c->curs == NULL || c->curs->next == NULL)
		return (false);
	if (c->curs->next->c == ' ')
		while (c->curs && c->curs->next && c->curs->next->c == ' ')
			move_right();
	else
		while (c->curs && c->curs->next && c->curs->next->c != ' ')
			move_right();
	return (true);
}
