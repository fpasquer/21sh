/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 19:27:10 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/26 22:06:23 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"

#define KEY_IGNORE -2
#define NONE 0
#define D_QUOTE '\"'
#define QUOTE '\''
#define PRINT_MAX 5

static char					cmd_keyboard(char b[SIZE_BUFF])
{
/*	if (ESC)
		key_exit(EXIT_SUCCESS);
	else if (F1)
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
		del_right();
	else*/ if ((b[0] >= 32 && b[0] <= 126) || ENTER)
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

/*static int					is_end(char c, t_line **lines)
{
	int						quote;
	t_entry					*curs;

	if (c != '\n')
		return (false);
	quote = NONE;
	curs = g_lines->line;
	while (curs != NULL)
	{
		if (curs->c == '\'' && (quote == NONE || quote == QUOTE))
			quote = (quote == NONE) ? QUOTE : NONE;
		if (curs->c == '\"' && (quote == NONE || quote == D_QUOTE))
			quote = (quote == NONE) ? D_QUOTE : NONE;
		curs = curs->next;
	}
	if (quote != NONE)
	{
		(*lines)->y++;
		if (((*lines)->next = ft_memalloc(sizeof(t_line))) == NULL)
			return (ERROR);
		(*lines) = (*lines)->next;
	}
	return ((quote == NONE) ? true : false);
}*/

static int					new_lines(int quote, t_line **lines)
{
	if (quote == NONE)
		return (true);
	(*lines)->y++;
	if (((*lines)->next = ft_memalloc(sizeof(t_line))) == NULL)
		return (ERROR);
	(*lines) = (*lines)->next;
	return (false);
}

static int					is_end(char c, t_line **lines)
{
	int						quote;
	t_entry					*curent_c;
	t_line					*curs;

	if (c != '\n')
		return (false);
	if (lines == NULL || *lines == NULL || (curs = g_lines) == NULL)
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
	return (new_lines(quote, lines));
}

static int					place_curs(void)
{
	size_t					i;
	size_t					y;
	size_t					len_total;
	t_line					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((curs = g_lines) == NULL)
		return (ERROR);
	y = 0;
	len_total = 0;
	while (curs != NULL)
	{
		y += curs->y;
		len_total = curs->x;
		curs = curs->next;
	}
	while (y-- > 0)
		if (put_cmd_term("up") == ERROR)
			return (ERROR);
	i = sh->len_prompt + len_total;
	while (i-- > 0)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	print_prompt();
	return (true);
}

static void					put_lines(void)
{
	char					buff[PRINT_MAX + 1];
	unsigned int			i;
	t_line					*curs;
	t_entry					*c_line;

	curs = g_lines;
	if (place_curs() == true)
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
			if (add_c_to_line(c, curs) == ERROR)
				return (ERROR);
		put_lines();
		if ((ret = is_end(c, &curs)) != false)
			break ;
	}
	return (ret);
}

static int					save_y(t_line **lines)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || lines == NULL || *lines == NULL)
		return (ERROR);
	(*lines)->y = (*lines)->i / sh->win.ws_col;
	(*lines)->x = (*lines)->i % sh->win.ws_col;
	return (true);
}

int							add_c_to_line(char c, t_line *lines)
{
	t_entry					*new;

	if ((new = ft_memalloc(sizeof(*new))) == NULL || lines == NULL)
		return (ERROR);
	new->c = c;
	if (lines->curs == NULL)
	{
		lines->curs = new;
		new->next = (lines->line != NULL) ? lines->line : NULL;
		lines->line = new;
	}
	else
	{
		if (lines->curs->next != NULL)
			lines->curs->next->prev = new;
		new->next = (lines->curs->next != NULL) ? lines->curs->next : NULL;
		lines->curs->next = new;
		new->prev = lines->curs;
		lines->curs = lines->curs->next;
	}
	lines->i++;
	lines->len++;
	return (save_y(&lines));
}

char						*make_tab(void)
{
	char					*tab;
	t_line					*curs;
	t_entry					*curent_c;

	if ((curs = g_lines) == NULL)
		return (NULL);
	while (curs != NULL)
	{
		printf("line->x = %zu, line->y = %zu\n", curs->x, curs->y);
		curs = curs->next;
	}
	tab = NULL;
	return (tab);
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
