/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_entree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:28:59 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/23 17:55:20 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#include <limits.h>

#define KEY_IGNORE -2
#define NONE 0
#define D_QUOTE '\"'
#define QUOTE '\''
#define CC curs->curs

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

static int					get_line_cmd(void)
{
	char					c;
	int						ret;

	ret = false;
	while (1)
	{
		c = get_char_keyboard();
		if (place_curs() == ERROR)
			return (ERROR);
		if (c != KEY_IGNORE && ft_isascii(c))
			if (add_c_to_line(c, &g_curs) == ERROR)
				return (ERROR);
		if (put_cmd() == ERROR)
			return (ERROR);
		check_words_builtins_exclame(c);
		if ((ret = is_end(c)) != false)
			break ;
	}
	return (ret);
}

int							save_y_x_line(t_line **lines)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || lines == NULL || *lines == NULL ||
			sh->win.ws_col == 0)
		return (ERROR);
	if ((*lines) == g_lines)
	{
		(*lines)->y = ((*lines)->len + sh->len_prompt) / sh->win.ws_col;
		(*lines)->x = ((*lines)->len + sh->len_prompt) % sh->win.ws_col;
		(*lines)->y_i = ((*lines)->i + sh->len_prompt) / sh->win.ws_col;
		(*lines)->x_i = ((*lines)->i + sh->len_prompt) % sh->win.ws_col;
	}
	else
	{
		(*lines)->y = (*lines)->len / sh->win.ws_col;
		(*lines)->x = (*lines)->len % sh->win.ws_col;
		(*lines)->y_i = (*lines)->i == ULONG_MAX ?
			0 : (*lines)->i / sh->win.ws_col;
		(*lines)->x_i = (*lines)->i == ULONG_MAX ?
			0 : (*lines)->i % sh->win.ws_col;
	}
	return (true);
}

char						*get_line_entree(bool srch)
{
	del_g_lines();
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL)
		return (NULL);
	g_curs = g_lines;
	if (srch == true)
		g_lines->h_srch = true;
	if (get_line_cmd() == ERROR)
		return (NULL);
	return (make_tab());
}
