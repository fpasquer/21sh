/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_print_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:13:38 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/13 22:16:09 by fcapocci         ###   ########.fr       */
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
	place_curs();
	insert_word_in_g_line(sh->hist->curs->line, &g_lines);
	return (true);
}

int							print_history_down(void)
{
	return (true);
}
