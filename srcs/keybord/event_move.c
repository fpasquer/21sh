/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:46:46 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/13 00:39:22 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static bool					g_move = false;

static int					get_new_i(t_21sh *sh, t_line *curs)
{
	size_t					i;

	if (sh == NULL || curs == NULL || g_lines == NULL)
		return (ERROR);
	i = (curs == g_lines) ? curs->i + sh->len_prompt : curs->i;
	if (curs->x_i == sh->win.ws_col - 2)
	{
		i = sh->win.ws_col - 1;
		while (i-- > 0)
			if (put_cmd_term("le") == ERROR)
				return (ERROR);
		if (put_cmd_term("do") == ERROR)
			return (ERROR);
	}
	else
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
	curs->i++;
	curs->curs = curs->curs == NULL ? curs->line : curs->curs->next;
	curs->y_i = (curs->x_i == sh->win.ws_col - 1) ? curs->y_i + 1 : curs->y_i;
	curs->x_i = (curs->x_i == sh->win.ws_col - 1) ? 0 : curs->x_i + 1;
	fprintf(debug, "move right curs == %c , %c , %c\n", curs->curs && curs->curs->prev ? curs->curs->prev->c : '0', curs->curs ? curs->curs->c : '0', curs->curs && curs->curs->next ? curs->curs->next->c : '0');
	return (true);
}

int							move_right(void)
{
	t_line					*curs;
	t_21sh					*sh;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	if (curs->len == 0)
		return (true);
	if (curs->i >= curs->len - 1 && curs->i != ULONG_MAX)
	{
		if (g_move == true)
			if (put_cmd_term("nb") == ERROR)
				return (ERROR);
		g_move = false;
		return (true);
	}
	return (get_new_i(sh, curs));
}

int							move_left(void)
{
	t_line					*curs;
	t_21sh					*sh;

	sh = get_21sh(NULL);
	if ((curs = g_lines) == NULL || sh == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	if (curs->curs != NULL)
	{
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
		curs->i--;
		curs->curs = curs->curs->prev;
		if (curs->x_i == 0 && curs->i < curs->len - 1)
		{
			curs->x_i = (curs->y_i > 0) ? sh->win.ws_col - 1 : curs->x_i;
			curs->y_i = (curs->y_i > 0) ? curs->y_i - 1 : curs->y_i;
		}
		else if (curs->i < curs->len - 1 || curs->i == ULONG_MAX)
			curs->x_i--;
	}
	fprintf(debug, "move left curs == %c , %c , %c\n", curs->curs && curs->curs->prev ? curs->curs->prev->c : '0', curs->curs ? curs->curs->c : '0', curs->curs && curs->curs->next ? curs->curs->next->c : '0');
	return (true);
}
