/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 07:37:39 by fpasquer          #+#    #+#             */
/*   Updated: 2016/11/02 14:19:32 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#define SHC sh->hist->curs

int							get_y_x_line(char *line, unsigned int *y,
		unsigned int *x)
{
	unsigned int			i;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || y == NULL || x == NULL)
		return (ERROR);
	(*x) = sh->len_prompt % sh->win.ws_col;
	(*y) = sh->len_prompt / sh->win.ws_col;
	i = 0;
	while (line[i] != '\0')
	{
		(*x) = (line[i] == '\n') ? 1 : (*x) + 1;
		(*y) = (line[i] == '\n') ? (*y) + 1 : (*y);
		if ((*x) > sh->win.ws_col)
		{
			(*y) = (*y) + 1;
			(*x) = 1;
		}
		i++;
	}
	return (true);
}

int							move_cursor(unsigned int y, unsigned int x)
{
	unsigned int			i;

	i = 0;
	if (y > 0)
		while (i++ <= y)
				if (put_cmd_term("up") == ERROR)
					return (ERROR);
	i = 0;
	while (i++ < x)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	return (put_cmd_term("cd"));
}

int							search_history_up(char *beguin)
{
	unsigned int			y;
	unsigned int			x;
	t_21sh					*sh;

	if (beguin == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((g_lines = ft_memalloc(sizeof(*g_lines))) == NULL)
		return (ERROR);
	g_curs = g_lines;
	if (sh->hist == NULL)
		return (true);
	if (SHC == NULL)
		SHC = sh->hist;
	else
		SHC = (SHC->next != NULL) ? SHC->next : SHC;
	if (get_y_x_line(beguin, &y, &x) == ERROR)
		return (ERROR);
	fprintf(debug, "\nx = %u, y = %u\n\n", x, y);
	if (move_cursor(y, x) == ERROR)
		return (ERROR);
	return (insert_word_in_g_line(SHC->line, &g_curs));
}

int							search_history_down(char *beguin)
{
	unsigned int			y;
	unsigned int			x;
	t_21sh					*sh;

	if (beguin == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (get_y_x_line(beguin, &y, &x) == ERROR)
		return (ERROR);
	if (move_cursor(y, x) == ERROR)
		return (ERROR);
	if ((g_lines = ft_memalloc(sizeof(*g_lines))) == NULL)
		return (ERROR);
	g_curs = g_lines;
	if (sh->hist == NULL || SHC == NULL)
		return (insert_word_in_g_line(beguin, &g_curs));
	SHC = SHC->prev;
	if (SHC == NULL || SHC->prev == NULL)
		return (insert_word_in_g_line("", &g_curs));
	return (insert_word_in_g_line(SHC->line, &g_curs));
}
