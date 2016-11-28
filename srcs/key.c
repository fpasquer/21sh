/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 19:27:10 by fpasquer          #+#    #+#             */
/*   Updated: 2016/11/28 22:12:29 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#include <limits.h>

#define KEY_IGNORE -2
#define NONE 0
#define D_QUOTE '\"'
#define QUOTE '\''
#define PRINT_MAX 500
#define CC curs->curs

static char					cmd_keyboard(char b[SIZE_BUFF])
{
	if (ESC)
		key_exit(EXIT_SUCCESS);
	else if (F1)
		key_del_hist();
	/*else if (F2)
		print_history();*/
	/*else if (TAB)
		autocompletion();*/
	else if (ARROW_UP)
		print_history_up();
	else if (ARROW_DOWN)
		;//print_history_down();
	else if (ARROW_RIGHT)
		move_right();
	else if (ARROW_LEFT)
		move_left();
	else if (DEL)
		del_left();
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
	g_lines->count_line++;
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

static int					loop_place_curs(size_t y, size_t x)
{
	while (y-- > 1)
		if (put_cmd_term("up") == ERROR)
			return (ERROR);
	while (x-- + 1 > 0)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	return (true);
}

char						last_c(t_line *line, size_t i)
{
	size_t					loop;
	t_entry					*curs;

	if (line != NULL && line->line != NULL)
	{
		curs = line->line;
		loop = 0;
		while (curs != NULL)
		{
			if (loop++ == i)
				return (curs->c);
			curs = curs->next;
		}
	}
	return ('0');
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
	while (curs != NULL)
	{
		loop = loop + 1;
		(*y) += curs->y_i;
		(*x) = curs->x_i;
		curs = curs->next;
	}
	(*y) += loop;
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

static int						clean_and_put_prompt(void)
{
	int							ret;

	ret = put_cmd_term("cd");
	print_prompt();
	return (ret);
}

static int					replace_i(void)
{
	size_t					i;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	i = curs->i;
	while (i++ + 1< curs->len)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	return (true);
}

int							put_cmd(void)
{
	char					buff[PRINT_MAX + 1];
	unsigned int			i;
	t_line					*curs;
	t_entry					*c_line;

	if (clean_and_put_prompt() != true || (curs = g_lines) == NULL)
		return (ERROR);
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
		if ((curs = curs->next) != NULL)
			ft_putchar('\n');
	}
	return (replace_i());
}

static int					creat_new_line(t_line **lines, char c)
{
	t_line					*new;

	if (c != '\n')
		return (false);
	if (lines == NULL || *lines == NULL || g_lines == NULL)
		return (ERROR);
	if ((new = ft_memalloc(sizeof(t_line))) == NULL)
		return (ERROR);
	(*lines)->next = new;
	(*lines) = (*lines)->next;
	return (true);
}

static int					get_line_cmd(void)
{
	char					c;
	int						ret;

	while (1)
	{
		if ((c = get_char_keyboard()) != KEY_IGNORE)
		{
			if (place_curs() == ERROR)
				return (ERROR);
			if (creat_new_line(&g_curs, c) == false)
				if (add_c_to_line(c, &g_curs) == ERROR)
					return (ERROR);
			if (put_cmd() == ERROR)
				return (ERROR);
		}
		if ((ret = is_end(c)) != false)
			break ;
	}
	return (ret);
}

int							save_y_x_line(t_line **lines, char c)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || lines == NULL || *lines == NULL ||
			sh->win.ws_col == 0)
		return (ERROR);
	if (c == '\n')
	{
		(*lines)->x = 0;
		(*lines)->y++;
		(*lines)->x_i = 0;
		(*lines)->y_i++;
	//fprintf(debug, "1 %c x = %3zu, y = %3zu x_i = %3zu y_i = %3zu, i = %3zu, len = %3zu\n", c, (*lines)->x, (*lines)->y, (*lines)->x_i, (*lines)->y_i,
			//(*lines)->i, (*lines)->len);
		return (true);
	}
	(*lines)->x = (*lines)->i == 0 && g_lines != g_curs ? ULONG_MAX : (*lines)->x;
	(*lines)->x_i = (*lines)->i == 0 && g_lines != g_curs ? ULONG_MAX : (*lines)->x_i;
	(*lines)->y_i = (*lines)->x_i + 1 >= sh->win.ws_col ? (*lines)->y_i + 1 :
			(*lines)->y_i;
	(*lines)->x_i = (*lines)->x_i + 1 >= sh->win.ws_col ? 0 : (*lines)->x_i + 1;
	(*lines)->y = (*lines)->x + 1 >= sh->win.ws_col ? (*lines)->y + 1 :
			(*lines)->y;
	(*lines)->x = (*lines)->x + 1 >= sh->win.ws_col ? 0 : (*lines)->x + 1;
	//fprintf(debug, "2 %c x = %3zu, y = %3zu x_i = %3zu y_i = %3zu, i = %3zu, len = %3zu\n", c, (*lines)->x, (*lines)->y, (*lines)->x_i, (*lines)->y_i,
	//		(*lines)->i, (*lines)->len);
	return (true);
}

static int					check_save_y_x(t_line **lines, char c)
{
	int						ret;

	if (lines == NULL || *lines == NULL)
		return (ERROR);
	(*lines)->i = ((*lines)->len == 0) ? 0 : (*lines)->i + 1;
	(*lines)->len++;
	return (save_y_x_line(lines, c));
}

int							add_c_to_line(char c, t_line **line)
{
	t_entry					*n;

	if ((n = ft_memalloc(sizeof(*n))) == NULL || line == NULL || *line == NULL)
		return (ERROR);
	n->c = c;
	if ((*line)->curs == NULL)
	{
		(*line)->curs = n;
		(*line)->i = ULONG_MAX;
		if ((n->next = (*line)->line) != NULL)
			(*line)->line->prev = n;
		(*line)->line = n;
	}
	else
	{
		if ((*line)->curs->next != NULL)
			(*line)->curs->next->prev = n;
		n->next = ((*line)->curs->next != NULL) ? (*line)->curs->next : NULL;
		(*line)->curs->next = n;
		n->prev = (*line)->curs;
		(*line)->curs = (*line)->curs->next;
	}
	return (check_save_y_x(line, c));
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
			if (curent_c->c != '\n')
				tab[i++] = curent_c->c;
			curent_c = curent_c->next;
		}
		if ((curs = curs->next) != NULL)
			tab[i++] = '\n';
	}
	del_g_lines();
	return(tab);
}

int							insert_word_in_g_line(char *word, t_line **line)
{
	unsigned int			i;

	if (word == NULL || line == NULL || *line == NULL)
		return (ERROR);
	if (ft_strlen(word) > 0)
	{
		i = 0;
		while (word[i++] != '\0')
			if (word[i - 1] != '\n' || word[i] != '\0')
				if (add_c_to_line(word[i - 1], line) == ERROR)
					return (ERROR);
	}
	return (true);
}

static int					place_curs_end_line(void)
{
	size_t					i;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs =  curs->next;
	i = curs->y_i;
	while (i++ < curs->y)
		if (put_cmd_term("do") == ERROR)
			return (ERROR);
	i = curs->x_i;
	while (i++ < curs->x)
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
	return (true);
}


static int					save_y_x(void)
{
	size_t					i;
	t_line					*curs;

	g_y = 0;
	g_x = 0;
	if ((curs = g_lines) == NULL)
		return (ERROR);
	i = 0;
	while (curs != NULL)
	{
		g_y += curs->y;
		i++;
		g_x = curs->x;
		curs = curs->next;
	}
	if (i > 0)
		g_y += i - 1;
	return (place_curs_end_line());
}

char						*make_tab(void)
{
	char					*tab;
	size_t					len_total;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ft_strdup(""));
	if (save_y_x() == ERROR)
		return (NULL);
	len_total = g_lines->count_line;
	while (curs != NULL)
	{
		len_total += curs->len;
		curs = curs->next;
	}
	if ((tab = ft_memalloc(sizeof(*tab) * (len_total + 1))) == NULL)
		return (NULL);
	return (save_tab(tab));
}


char						*get_line_entree(void)
{
	t_21sh					*sh;

	if ((sh =get_21sh(NULL)) == NULL)
		return (NULL);
	del_g_lines();
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL)
		return (NULL);
	g_curs = g_lines;
	g_curs->x = (sh->len_prompt - 1) % sh->win.ws_col;
	g_curs->x_i = (sh->len_prompt - 1) % sh->win.ws_col;
	g_curs->y = (sh->len_prompt - 1) / sh->win.ws_col;
	g_curs->y_i = (sh->len_prompt - 1) / sh->win.ws_col;
	if (get_line_cmd() == ERROR)
		return (NULL);
	return (make_tab());
}
