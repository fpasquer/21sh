/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 21:42:08 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/07 09:06:07 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

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
	char					*tab;
	int						ret;


	if ((tab = make_tab()) == NULL)
		return (ERROR);
	ret = search_history_up(tab);
	ft_memdel((void**)&tab);
	return (ret);
}

int							print_history_down(void)
{
	char					*tab;
	int						ret;

	if ((tab = make_tab()) == NULL)
		return (ERROR);
	ret = search_history_down(tab);
	ft_memdel((void**)&tab);
	return (ret);
}

static int					get_new_i(t_21sh *sh, t_line *curs)
{
	size_t					i;

	if (sh == NULL || curs == NULL || g_lines == NULL)
		return (ERROR);
	i = (curs == g_lines) ? curs->i + sh->len_prompt : curs->i;
	//if (i % sh->win.ws_col == sh->win.ws_col - 1)
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
																				//fprintf(debug, "righ i = %3zu x_i = %3zu y_i = %3zu len = %3zu c = %c\n", i, curs->x_i, curs->y_i, curs->len, last_c(curs, curs->i));
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
//		if (g_move == false)
//			return ((g_move = true));
		if (curs->x_i == 0 && curs->i < curs->len - 1)
		{
			curs->x_i = (curs->y_i > 0) ? sh->win.ws_col - 1 : curs->x_i;
			curs->y_i = (curs->y_i > 0) ? curs->y_i - 1 : curs->y_i;
		}
		else if (curs->i < curs->len - 1 || curs->i == ULONG_MAX)
			curs->x_i--;
																				//fprintf(debug, "left i = %3zu x_i = %3zu y_i = %3zu len = %3zu c = %c\n", curs->i, curs->x_i, curs->y_i, curs->len, last_c(curs, curs->i));
	}
	return (true);
}

static int					save_info_line(t_line **line)
{
	int						ret;
	t_21sh					*sh;

	if (line == NULL || *line == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
																				//fprintf(debug, "1 x = %3zu, y = %3zu i = %3zu len = %3zu\n", (*line)->x_i, (*line)->y_i, (*line)->i, (*line)->len);
																				//fprintf(debug, "i == %3zu line : %3d\n", (*line)->i, __LINE__);
	(*line)->i--;
	(*line)->len--;
																				//fprintf(debug, "i == %3zu line : %3d\n", (*line)->i, __LINE__);
	if ((*line)->x_i == 0)
	{
		(*line)->x_i = ((*line)->y_i > 0) ? sh->win.ws_col - 1 : (*line)->x_i;
		(*line)->y_i = ((*line)->y_i > 0) ? (*line)->y_i - 1 : (*line)->y_i;
	}
	else
		(*line)->x_i--;
																				//fprintf(debug, "g_lines->y_i == %3zu line : %3d\n", (*line)->y_i, __LINE__);
	if (save_y_x_line(line) == ERROR)
		return (ERROR);
																			//fprintf(debug, "2 x = %3zu, y = %3zu i = %3zu len = %3zu\n", (*line)->x_i, (*line)->y_i, (*line)->i, (*line)->len);
																			//fprintf(debug, " del i = %3zu x_i = %3zu y_i = %3zu len = %3zu\n", (*line)->i, (*line)->x_i, (*line)->y_i, (*line)->len);
	return (put_cmd());
}

static int					del_left_line(t_line *curs, t_entry *tmp)
{
	if (curs == NULL || curs->curs == NULL || curs->curs->c == '\n')
		return (ERROR);
																				//fprintf(debug, "line %d curs->curs = %p curs->y_i = %3zu\n", __LINE__, curs->curs, curs->y_i);
	if (place_curs() == ERROR)
		return (ERROR);
																				//fprintf(debug, "line %d curs->curs = %p curs->y_i = %3zu\n", __LINE__, curs->curs, curs->y_i);
	if (curs->curs->next != NULL)
		curs->curs->next->prev = curs->curs->prev;
	if (curs->curs->prev != NULL)
		curs->curs->prev->next = curs->curs->next;
	if (curs->curs == curs->line)
	{
																				//fprintf(debug, "c = %p\n", curs->line->next);
		curs->line = curs->line->next;
		tmp = curs->line;
	}
	else
		tmp = curs->curs->prev;
	if (save_info_line(&curs) == ERROR)
		return (ERROR);
	ft_memdel((void**)&curs->curs);
	curs->curs = tmp;
																				//fprintf(debug, "%d curs = %3zu\n",__LINE__, g_lines->y_i);
																				//fprintf(debug, "line %d curs->curs = %p curs->y_i = %3zu\n", __LINE__, curs->curs, curs->y_i);
	return (true);
}

int							del_left(void)
{
	t_line					*curs;
	t_entry					*tmp;

																				//fprintf(debug, "%d curs = %p ",__LINE__, g_lines->curs);
	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
																				//fprintf(debug, "line %d curs->curs = %p, curs->y_i = %3zu\n", __LINE__, curs->curs, curs->y_i);
	if (curs->curs != NULL && curs->curs->c != '\n')
		return (del_left_line(curs, tmp));
	return(true);
}
