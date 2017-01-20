/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_selec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 20:12:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/20 18:43:10 by fcapocci         ###   ########.fr       */
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
	cpy = curs->curs;
	while (cpy)
	{
		cpy->select = false;
		cpy = cpy->next;
	}
	curs->activity = false;
	return (ret);
}

int					selec_mode(void)
{
	t_line			*curs;
	char			b[SIZE_BUFF];

	ft_bzero(b, sizeof(b));
	if ((curs = g_curs) == NULL)
		return (false);
	curs->activity = true;
	while (curs->len > 0 && !SEL_MOD)
	{
		ft_bzero(b, sizeof(b));
		if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0)
			return (reset_selec(false));
		else if (ARROW_RIGHT)
			move_right();
		else if (ARROW_LEFT)
			move_left();
		/*else if (CTRL_CPY)
		{
			event_cpy();
			reset_selec(true);
			break ;
		}
		else if (CTRL_CUT)
		{
			event_cut();
			reset_selec(true);
			break ;
		}*/
	}
	reset_selec(true);
	return (true);
}
