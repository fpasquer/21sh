/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 19:27:10 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/08 11:33:32 by fpasquer         ###   ########.fr       */
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
		print_history_down();
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
//getchar();
	while (x-- + 1 > 0)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
//getchar();
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
																				//fprintf(debug, "%d y_i = %3zu %11p ", __LINE__, g_lines->y_i, g_lines->curs);
	if (sh == NULL || (curs = g_lines) == NULL || y == NULL || x == NULL)
		return (ERROR);
																				//fprintf(debug, "%d y_i = %3zu %11p 'line : %d'\n", __LINE__, curs->y_i, curs->curs, __LINE__);
	loop = 0;
	(*x) = sh->len_prompt;
	(*y) = 0;
																				//fprintf(debug, "%d y_i = %3zu %11p 'line : %d'\n", __LINE__, curs->y_i, curs->curs, __LINE__);
	if (curs->x_i == 0 && curs->y_i == 0)
		return (true);

																				//fprintf(debug, "%d y_i = %3zu %11p 'line : %d'\n", __LINE__, curs->y_i, curs->curs, __LINE__);
																				//fprintf(debug, "%d y_i = %3zu ", __LINE__, (*y));
	while (curs != NULL)
	{
																				//fprintf(debug, " acteul = %3zu ", curs->y_i);
		loop++;
																				//fprintf(debug, "loop = %3zu\n", loop);
																				//fprintf(debug, "(*y) = %3zu\n", (*y));
																				//fprintf(debug, "%d y_i = %3zu %11p 'line : %d'\n", __LINE__, curs->y_i, curs->curs, __LINE__);
		(*y) += curs->y_i;
																				//fprintf(debug, "(*y) = %3zu\n", (*y));
		(*x) = curs->x_i;
																				//fprintf(debug, "(*x) = %3zu\n", (*x));
		curs = curs->next;
	}
																				//fprintf(debug, " ret = %3zu\n", (*y));
	(*y) += loop;
																				if ((*y) > 10)
																				{
																					//fprintf(debug, "y = %3zu loop = %3zu\n", (*y), loop);
																					exit(0);
																				}
																			//	fprintf(debug, "y = %3zu x %3zu loop = %3zu i = %3zu len = %3zu\n", (*y) - loop, (*x), loop, i_last, len_last);
																				//fprintf(debug, "%d y_i = %3zu ", __LINE__, g_lines->y_i);
	return (true);
}

int							place_curs(void)
{
	size_t					i;
	size_t					y;

																				//fprintf(debug, "%d y_i = %3zu ", __LINE__, g_lines->y_i);
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

/*int							put_lines(void)
{

	if (place_curs() == true)
		return (put_cmd());
	return (ERROR);
}*/

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
			if (add_c_to_line(c, &g_curs) == ERROR)
				return (ERROR);
			if (put_cmd() == ERROR)
				return (ERROR);
																				//fprintf(debug, "%d y_i = %3zu\n", __LINE__, g_lines->y_i);
		}
		if ((ret = is_end(c)) != false)
			break ;
	}
	return (ret);
}

int							save_y_x_line(t_line **lines)
{
	size_t					y;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || lines == NULL || *lines == NULL ||
			sh->win.ws_col == 0)
		return (ERROR);

																				//fprintf(debug, "\ty = %3zu x %3zu i = %3zu len = %3zu line : %d\n", (*lines)->y_i , (*lines)->x_i, (*lines)->i, (*lines)->len, __LINE__);
	if ((*lines) == g_lines)
	{
																				//fprintf(debug, "ici");
		(*lines)->y = ((*lines)->len + sh->len_prompt) / sh->win.ws_col;
		(*lines)->x = ((*lines)->len + sh->len_prompt) % sh->win.ws_col;
		(*lines)->y_i = ((*lines)->i + sh->len_prompt) / sh->win.ws_col;
		(*lines)->x_i = ((*lines)->i + sh->len_prompt) % sh->win.ws_col;
	}
	else
	{
																				//fprintf(debug, "la");
		(*lines)->y = (*lines)->len / sh->win.ws_col;
		(*lines)->x = (*lines)->len % sh->win.ws_col;
		(*lines)->y_i = (*lines)->i == ULONG_MAX ? 0 : (*lines)->i / sh->win.ws_col;
		(*lines)->x_i = (*lines)->i == ULONG_MAX ? 0 : (*lines)->i % sh->win.ws_col;
	}

																				fprintf(debug, " y = %3zu x %3zu i = %3zu len = %3zu line : %d\n", (*lines)->y_i , (*lines)->x_i, (*lines)->i, (*lines)->len, __LINE__);
	return (true);
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

static int					check_save_y_x(t_line **lines, char c)
{
	int						ret;

	if (lines == NULL || *lines == NULL)
		return (ERROR);
	(*lines)->i = ((*lines)->len == 0) ? 0 : (*lines)->i + 1;
	(*lines)->len++;
	ret = save_y_x_line(lines);
	return (ret);
}

int							add_c_to_line(char c, t_line **line)
{
	t_entry					*n;

	if (creat_new_line(line, c) == true)
		return (true);
	if ((n = ft_memalloc(sizeof(*n))) == NULL || line == NULL || *line == NULL)
		return (ERROR);
	n->c = c;
																				fprintf(debug, "c = %2c = %p", c, n);
	if ((*line)->curs == NULL || (*line)->i == ULONG_MAX)
	{
																				//fprintf(debug, "%d c = %c ", __LINE__, c);
		(*line)->curs = n;
		(*line)->i = ULONG_MAX;
		if ((n->next = (*line)->line) != NULL)
			(*line)->line->prev = n;
		(*line)->line = n;
	}
	else
	{
																				//fprintf(debug, "\n%d c = %c\n", __LINE__,  c);
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
		while (word[i] != '\0')
			if (add_c_to_line(word[i++], line) == ERROR)
				return (ERROR);
	}
	return (put_cmd());
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
																			//fprintf(debug, "len_total = %3zu\n", len_total);
	if ((tab = ft_memalloc(sizeof(*tab) * (len_total + 1))) == NULL)
		return (NULL);
	return (save_tab(tab));
}


char						*get_line_entree(void)
{
	del_g_lines();
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL)
		return (NULL);
	g_curs = g_lines;
	if (get_line_cmd() == ERROR)
		return (NULL);
	return (make_tab());
}
