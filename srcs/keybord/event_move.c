/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:46:46 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/03 05:28:23 by fcapocci         ###   ########.fr       */
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
	selec_manager(2);
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
	{
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
	}
	curs->i++;
	curs->curs = curs->curs == NULL ? curs->line : curs->curs->next;
	curs->y_i = (curs->x_i == sh->win.ws_col - 1) ? curs->y_i + 1 : curs->y_i;
	curs->x_i = (curs->x_i == sh->win.ws_col - 1) ? 0 : curs->x_i + 1;
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
	if (curs->len == 0 || curs->i == curs->len - 1)
		return (false);
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
		selec_manager(1);
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
	return (true);
}

int							move_start_line(void)
{
	t_line					*curs;

	if ((curs = g_curs) == NULL || curs->curs == NULL)
		return (false);
	while (curs->i != ULONG_MAX)
		move_left();
	return (true);
}

int							move_end_line(void)
{
	t_line					*curs;

	if ((curs = g_curs) == NULL || curs->len == 0)
		return (false);
	if (curs->i == ULONG_MAX)
		move_right();
	while (curs->curs->next)
		move_right();
	return (true);
}
