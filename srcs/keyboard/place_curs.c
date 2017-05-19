/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_curs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:17:50 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/19 13:52:49 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"
#include <limits.h>

static int					loop_place_curs(size_t y, size_t x)
{
	if (y > 10)
	{
		fprintf(debug, "line : %d : y = %zu x = %zu\n", __LINE__, y, x);
		exit(10);
	}
	while (y-- > 1)
		if (put_cmd_term("up") == ERROR)
			return (ERROR);
	while (x-- + 1 > 0)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	return (true);
}

static int					save_y_i(size_t *y, size_t *x)
{
	size_t					loop;
	t_line					*curs;
	t_21sh					*sh;

	sh = get_21sh(NULL);
	if (sh == NULL || (curs = g_lines) == NULL || y == NULL || x == NULL)
		return (ERROR);
	loop = 0;
	(*x) = sh->len_prompt;
	(*y) = 0;
	if (curs->x_i == 0 && curs->y_i == 0)
		return (true);
	fprintf(debug, "line : %d : y = %zu x = %zu\n", __LINE__, *y, *x);
	while (curs != NULL)
	{
		loop++;
		(*y) += curs->y_i;
		(*x) = curs->x_i;
		curs = curs->next;
	}
	(*y) += loop;
	fprintf(debug, "\tline : %d : y = %zu x = %zu\n", __LINE__, *y, *x);
	return (true);
}

int							place_curs(void)
{
	size_t					i;
	size_t					y;

	if (save_y_i(&y, &i) == ERROR)
		return (ERROR);
	return (loop_place_curs(y, i));
}
