/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_print_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:13:38 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/18 20:04:59 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

static int					reset_g_curs(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL || g_lines == NULL)
		return (ERROR);
	ft_bzero(g_curs, sizeof(*g_curs));
	if (g_curs == g_lines)
	{
		g_curs->x = (sh->len_prompt - 1) % sh->win.ws_col;
		g_curs->x_i = (sh->len_prompt - 1) % sh->win.ws_col;
		g_curs->y = (sh->len_prompt - 1) / sh->win.ws_col;
		g_curs->y_i = (sh->len_prompt - 1) / sh->win.ws_col;
	}
	return (true);
}

static int					change_value_g_curs_line(char *word)
{
	size_t					i;
	t_entry					*curs;
	t_entry					*mem;

	if (g_curs == NULL)
		return (false);
	if (place_curs() == ERROR)
		return (ERROR);
	curs = g_curs->line;
	while (curs != NULL)
	{
		mem = curs->next;
		ft_memdel((void**)&curs);
		curs = mem;
	}
	if (reset_g_curs() == ERROR)
		return (ERROR);
	i = 0;
	if (insert_word_in_g_line(word, &g_curs))
		return (ERROR);
	return (true);
}

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
	if (change_value_g_curs_line(sh->hist->curs->line) != true)
		return (false);
	return (true);
}

int							print_history_down(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || sh->hist == NULL)
		return (false);
	if (sh->hist->curs == NULL)
		return (false);
	else
		sh->hist->curs = sh->hist->curs->prev;
	if (sh->hist->curs == NULL)
		return (change_value_g_curs_line(""));
	else
		return (change_value_g_curs_line(sh->hist->curs->line));
}
