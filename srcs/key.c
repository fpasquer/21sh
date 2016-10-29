/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 19:27:10 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/29 15:34:36 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#include <limits.h>

#define KEY_IGNORE -2
#define NONE 0
#define D_QUOTE '\"'
#define QUOTE '\''
#define PRINT_MAX 5

static char					cmd_keyboard(char b[SIZE_BUFF])
{
	if (ESC)
		key_exit(EXIT_SUCCESS);
	/*else if (F1)
		key_del_hist();
	else if (F2)
		print_history();
	else if (TAB)
		autocompletion();
	else if (ARROW_UP)
		print_history_up();
	else if (ARROW_DOWN)
		print_history_down();
	else if (ARROW_RIGHT)
		mouve_righ();
	else if (ARROW_LEFT)
		mouve_left();
	else if (DEL)
		del_right();*/
	else if ((b[0] >= 32 && b[0] <= 126) || ENTER)
		return (b[0]);
	return (KEY_IGNORE);
}

static char					get_char_keyboard(void)
{
	char					b[SIZE_BUFF];

	ft_bzero(b, sizeof(b));
	if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0)
		return (ERROR);
	return (cmd_keyboard(b));
}

static int					is_end(char c)
{
	int						quote;
	t_entry					*curent_c;
	t_line					*curs;

	if (c != '\n')
		return (false);
	if ((curs = g_lines) == NULL)
		return (ERROR);
	quote = NONE;
	while (curs != NULL)
	{
		curent_c = curs->line;
		while (curent_c != NULL)
		{
			if (curent_c->c == '\'' && (quote == NONE || quote == QUOTE))
				quote = (quote == NONE) ? QUOTE : NONE;
			if (curent_c->c == '\"' && (quote == NONE || quote == D_QUOTE))
				quote = (quote == NONE) ? D_QUOTE : NONE;
			curent_c = curent_c->next;
		}
		curs = curs->next;
	}
	return ((quote == NONE) ? true : false);
}

static int					loop_place_curs(size_t y, size_t i)
{
	if (y > 0)
		while (--y > 1)
			if (put_cmd_term("up") == ERROR)
				return (ERROR);
	if (i > 0)
		while (--i > 0)
			if (put_cmd_term("le") == ERROR)
				return (ERROR);
	return (true);
}

static int					save_y_i(size_t *y, size_t *i)
{
	size_t					len_last;
	size_t					last_y;
	t_line					*curs;
	t_21sh					*sh;

	sh = get_21sh(NULL);
	if (sh == NULL || (curs = g_lines) == NULL || y == NULL || i == NULL)
		return (ERROR);
	len_last = 0;
	(*i) = 0;
	(*y) = 0;
	last_y = 0;
	while (curs != NULL)
	{
		(*i) = (*i) + 1;
		(*y) += curs->y;
		last_y = curs->y;
		len_last = curs->x;
		curs = curs->next;
	}
	(*y) = g_lines->next && g_lines->x < sh->win.ws_col && g_lines->y == 0 &&
			len_last > 2 ? (*y) + 1 : (*y);
	(*y) += (*i);
	(*i) = ((*y) == 1) ? sh->len_prompt + len_last : sh->win.ws_col + len_last;
	return (true);
}

static int					place_curs(void)
{
	size_t					i;
	size_t					y;
	t_21sh					*sh;

	if (save_y_i(&y, &i) == ERROR || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (g_lines != NULL && g_lines->next != NULL && g_lines->x < sh->win.ws_col
			&& g_lines->next->len == 2)
		y++;
	return (loop_place_curs(y, i));
}

static int						clean_and_put_prompt(void)
{
	int							ret;

	ret = put_cmd_term("cd");
	print_prompt();
	return (ret);
}

static void					put_lines(void)
{
	char					buff[PRINT_MAX + 1];
	unsigned int			i;
	t_line					*curs;
	t_entry					*c_line;

	if (place_curs() == true && (curs = g_lines) != NULL &&
			clean_and_put_prompt() == true)
		while (curs != NULL)
		{
			c_line = curs->line;
			while (c_line != NULL)
			{
				i = 0;
				ft_bzero(buff, sizeof(buff));
				while (c_line != NULL && i < PRINT_MAX)
				{
					buff[i++] = c_line->c;
					c_line = c_line->next;
				}
				ft_putstr(buff);
			}
			curs = curs->next;
		}
}

static int					get_line_cmd(void)
{
	char					c;
	int						ret;
	t_line					*curs;

	curs = g_lines;
	while (1)
	{
		if ((c = get_char_keyboard()) != KEY_IGNORE)
		{
			if (add_c_to_line(c, &curs) == ERROR)
				return (ERROR);
			put_lines();
		}
		if ((ret = is_end(c)) != false)
			break ;
	}
	return (ret);
}

static int					save_y(t_line **lines)
{
	size_t					y;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || lines == NULL || *lines == NULL)
		return (ERROR);
	if (sh->win.ws_col == 0)
		return (false);
	if ((*lines) == g_lines)
	{
		(*lines)->y = ((*lines)->i + sh->len_prompt) / sh->win.ws_col;
		(*lines)->x = ((*lines)->i + sh->len_prompt) % sh->win.ws_col;
	}
	else
	{
		(*lines)->y = (*lines)->i / sh->win.ws_col;
		(*lines)->x = (*lines)->i % sh->win.ws_col;
	}
	return (true);
}

static void					creat_new_line(t_line **lines, char c)
{
	t_line					*new;

	if (c != '\n')
		return ;
	if (lines == NULL || *lines == NULL)
		return ;
	if ((new = ft_memalloc(sizeof(t_line))) == NULL)
		return ;
	(*lines)->next = new;
	(*lines) = (*lines)->next;
}

int							add_c_to_line(char c, t_line **lines)
{
	t_entry					*n;

	creat_new_line(lines, c);
	if ((n = ft_memalloc(sizeof(*n))) == NULL || lines == NULL ||
			*lines == NULL)
		return (ERROR);
	n->c = c;
	if ((*lines)->curs == NULL)
	{
		(*lines)->curs = n;
		n->next = ((*lines)->line != NULL) ? (*lines)->line : NULL;
		(*lines)->line = n;
	}
	else
	{
		if ((*lines)->curs->next != NULL)
			(*lines)->curs->next->prev = n;
		n->next = ((*lines)->curs->next != NULL) ? (*lines)->curs->next : NULL;
		(*lines)->curs->next = n;
		n->prev = (*lines)->curs;
		(*lines)->curs = (*lines)->curs->next;
	}
	(*lines)->i++;
	(*lines)->len++;
	return (save_y(lines));
}

static char					*save_tab(char *tab)
{
	size_t					i;
	t_line					*curs;
	t_entry					*curent_c;

	if((curs = g_lines) == NULL || tab == NULL)
		return (NULL);
	i = 0;
	while (curs != NULL)
	{
		curent_c = curs->line;
		while (curent_c != NULL)
		{
			tab[i++] = curent_c->c;
			curent_c = curent_c->next;
		}
		curs = curs->next;
	}
	return(tab);
}

char						*make_tab(void)
{
	char					*tab;
	size_t					len_total;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (NULL);
	len_total = 0;
	while (curs != NULL)
	{
		len_total += curs->len;
		curs = curs->next;
	}
	if ((tab = ft_memalloc(sizeof(*tab) * len_total)) == NULL)
		return (NULL);
	return (save_tab(tab));
}


char						*get_line_entree(void)
{
	del_g_lines();
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL)
		return (NULL);
	if (get_line_cmd() == ERROR)
		return (NULL);
	return (make_tab());
}
