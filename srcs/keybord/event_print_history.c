/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_print_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:13:38 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/13 23:00:43 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

int							print_history_up(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || sh->hist == NULL)
		return (false);
	if (sh->hist->curs == NULL)
		sh->hist->curs = sh->hist;
	else if (sh->hist->curs->next == NULL)
		return (false);
	else
		sh->hist->curs = sh->hist->curs->next;
	change_value_g_curs_line(sh->hist->curs->line);
	return (true);
}

int							print_history_down(void)
{
	return (true);
}
