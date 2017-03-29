/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:21:19 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/29 11:24:22 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void						key_exit(unsigned char val_exit)
{
	ft_putendl(COLOR_LINE);
	put_cmd_term("cd");
	ft_putstr("exit");
	ft_putendl(RESET_COLOR);
	del_g_lines();
	del_21sh();
	exit(val_exit);
}

int							key_del_hist(void)
{
	t_history				*next;
	t_21sh					*sh;

	ft_putendl(COLOR_LINE);
	ft_putstr("del history");
	ft_putendl(RESET_COLOR);
	if ((sh = get_21sh(NULL)) != NULL)
		while (sh->hist != NULL)
		{
			next = sh->hist->next;
			ft_memdel((void**)&sh->hist->line);
			ft_memdel((void**)&sh->hist);
			sh->hist = next;
		}
	print_prompt();
	return (true);
}

static int					save_info_line(t_line **line)
{
	t_21sh					*sh;

	if (line == NULL || *line == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	(*line)->i--;
	(*line)->len--;
	if ((*line)->x_i == 0)
	{
		(*line)->x_i = ((*line)->y_i > 0) ? sh->win.ws_col - 1 : (*line)->x_i;
		(*line)->y_i = ((*line)->y_i > 0) ? (*line)->y_i - 1 : (*line)->y_i;
	}
	else
		(*line)->x_i--;
	if (save_y_x_line(line) == ERROR)
		return (ERROR);
	return (put_cmd());
}

static int					del_left_line(t_line *curs, t_entry *tmp)
{
	if (curs == NULL || curs->curs == NULL || curs->curs->c == '\n')
		return (ERROR);
	if (place_curs() == ERROR)
		return (ERROR);
	if (curs->curs->next != NULL)
		curs->curs->next->prev = curs->curs->prev;
	if (curs->curs->prev != NULL)
		curs->curs->prev->next = curs->curs->next;
	if (curs->curs == curs->line)
	{
		curs->line = curs->line->next;
		tmp = NULL;
	}
	else
		tmp = curs->curs->prev;
	if (save_info_line(&curs) == ERROR)
		return (ERROR);
	ft_memdel((void**)&curs->curs);
	curs->curs = tmp;
	return (true);
}

int							del_left(void)
{
	t_line					*c;

	if ((c = g_curs) == NULL)
		return (ERROR);
	if (c->curs != NULL && c->curs->c != '\n')
		return (del_left_line(c, NULL));
	return (true);
}
