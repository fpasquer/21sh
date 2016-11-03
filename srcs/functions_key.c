/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 21:42:08 by fpasquer          #+#    #+#             */
/*   Updated: 2016/11/03 11:58:23 by fpasquer         ###   ########.fr       */
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
	getchar();
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

/*static int					get_new_i(t_21sh *sh, t_line *curs)
{
	size_t					i;

	if (sh == NULL || curs == NULL)
		return (ERROR);
	if ((curs->i + sh->len_prompt + 1) % sh->win.ws_col == 0)
	{
		i = curs->i + sh->len_prompt;
		while (i-- > 0)
			if (put_cmd_term("le") == ERROR)
				return (ERROR);
		if (put_cmd_term("do") == ERROR)
			return (ERROR);
		curs->curs = curs->curs == NULL ? curs->line : curs->curs->next;
	}
	curs->i++;
	if (put_cmd_term("nd") == ERROR)
		return (ERROR);
	curs->curs = curs->curs == NULL ? curs->line : curs->curs->next;
	return (true);
}*/

static int					get_new_i(t_21sh *sh, t_line *curs)
{
	size_t					i;

	if (sh == NULL || curs == NULL)
		return (ERROR);
	i = (curs == g_lines) ? curs->i + sh->len_prompt : curs->i;
	fprintf(debug, "i = %3zu len = %3zu\n", curs->i, curs->len);
	if (i % sh->win.ws_col == sh->win.ws_col - 1)
	{
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
	if (curs->i > curs->len)
		return (true);
	return (get_new_i(sh, curs));
}


int							move_left(void)
{
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	if (curs->curs != NULL)
		if (curs == g_lines || curs->curs->prev != NULL)
		{
			if (put_cmd_term("le") == ERROR)
				return (ERROR);
			curs->i--;
			curs->curs = curs->curs->prev;
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
	if (save_y_x_line(line) == ERROR)
		return (ERROR);
	if ((*line)->y > 0)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	return (put_lines());
}

int							del_right(void)
{
	t_line					*curs;
	t_entry					*tmp;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	if (curs->curs != NULL && curs->curs->c != '\n')
	{
		if (curs->curs->next != NULL)
			curs->curs->next->prev = curs->curs->prev;
		if (curs->curs->prev != NULL)
			curs->curs->prev->next = curs->curs->next;
		if (curs->curs == curs->line)
			curs->line = curs->line->next;
		if (put_cmd_term("le") == ERROR || put_cmd_term("dc") == ERROR)
			return (ERROR);
		if (save_info_line(&curs) == ERROR)
			return (ERROR);
		tmp = curs->curs->prev;
		ft_memdel((void**)&curs->curs);
		curs->curs = tmp;
	}
	return(true);
}
