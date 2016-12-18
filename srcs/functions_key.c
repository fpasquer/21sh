/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 21:42:08 by fpasquer          #+#    #+#             */
/*   Updated: 2016/12/16 13:38:49 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#define SHC sh->hist->curs
#define CC curs->curs

static bool					g_move = false;

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
	t_history					*next;
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

int							print_history_up(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (sh->hist == NULL)
		return (true);
	if (SHC == NULL)
		SHC = sh->hist;
	else
		SHC = (SHC->next != NULL) ? SHC->next : SHC;
	if (change_value_g_curs_line(SHC->line) == ERROR)
		return (ERROR);
	return (put_cmd());
}

/*int							print_history_down(void)
{
	char					*tab;
	int						ret;

	if ((tab = make_tab()) == NULL)
		return (ERROR);
	ret = search_history_down(tab);
	ft_memdel((void**)&tab);
	return (ret);
}*/

int							print_history_down(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (sh->hist == NULL)
		return (true);
	if (SHC == NULL)
		SHC = sh->hist;
	else
		SHC = (SHC->prev != NULL) ? SHC->prev : SHC;
	if (change_value_g_curs_line(SHC->line) == ERROR)
		return (ERROR);
	return (put_cmd());
}


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

static int					is_enter_left(t_line **line)
{
	size_t					i;
	t_entry					*c_prev;
	t_21sh					*sh;

	if (line == NULL || *line == NULL || (*line)->curs == NULL ||
			(sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((c_prev = (*line)->curs->prev) == NULL)
		return (true);
	(*line)->x_i = c_prev->x_i + 1;
	(*line)->y_i = c_prev->y_i;
																				fprintf(debug, "up is_enter_left\n");
	if (put_cmd_term("up") == ERROR)
		return (ERROR);
	i = 0;
	if ((*line)->curs->x_i > 0)
		while (i++ <= (*line)->curs->x_i)
		{
																				fprintf(debug, "nd %3zu is_enter_left\n", i - 1);
			if (put_cmd_term("nd") == ERROR)
				return (ERROR);
		}
																				fprintf(debug, "line->x_i = %3zu line->y_i = %3zu\n", (*line)->x_i, (*line)->y_i);
	return (true);
}

int							move_left(void)
{
	t_line					*curs;
	t_21sh					*sh;

	sh = get_21sh(NULL);
	if ((curs = g_lines) == NULL || sh == NULL)
		return (ERROR);
	while (curs != NULL && curs->next != NULL)
		curs = curs->next;
	if (curs != NULL && curs->curs != NULL)
	{
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
		curs->i--;
		curs->curs = curs->curs->prev;
																				fprintf(debug, "p = %p le left\n", curs->curs);
		if (CC != NULL && CC->next != NULL && curs->curs->next->c == '\n')
			return (is_enter_left(&curs));
		if (curs->curs != NULL && curs->x_i == 0 && curs->i < curs->len - 1)
		{
																				//fprintf(debug, "line : %d\n", __LINE__);
			curs->x_i = (CC->prev != NULL) ? CC->x_i : CC->x_i;
			curs->y_i = (CC->prev != NULL) ? CC->y_i : CC->y_i;
		}
		else if (curs->i < curs->len - 1 || curs->i == ULONG_MAX)
																				{
																					//fprintf(debug, "line : %d\n", __LINE__);
			curs->x_i--;
																				}
																				fprintf(debug, "line->x_i = %3zu line->y_i = %3zu\n", curs->x_i, curs->y_i);
	}
	return (true);
}

static int					save_info_line(t_line **line)
{
	int						ret;
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
	if (save_y_x_line(line, '@') == ERROR)
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
		curs->line = curs->line->next;
	if (save_info_line(&curs) == ERROR)
		return (ERROR);
	tmp = curs->curs->prev;
	ft_memdel((void**)&curs->curs);
	curs->curs = tmp;
	return (true);
}

int							del_left(void)
{
	t_line					*curs;
	t_entry					*tmp;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	if (curs->curs != NULL && curs->curs->c != '\n')
		return (del_left_line(curs, tmp));
	return(true);
}
