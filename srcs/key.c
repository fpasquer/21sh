/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 10:58:55 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/17 17:15:51 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"

#define KEY_IGNORE -2

static char					cmd_keyboard(char b[SIZE_BUFF])
{
	if (ESC)
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

int							add_c_to_line(char c)
{
	t_entry					*new;

	if (c == '\n')
		return (true);
	if ((new = ft_memalloc(sizeof(*new))) == NULL)
		return (ERROR);
	new->c = c;
	if (g_lines.curs == NULL)
	{
		g_lines.curs = new;
		new->next = (g_lines.line != NULL) ? g_lines.line : NULL;
		g_lines.line = new;
	}
	else
	{
		if (g_lines.curs->next != NULL)
			g_lines.curs->next->prev = new;
		new->next = (g_lines.curs->next != NULL) ? g_lines.curs->next : NULL;
		g_lines.curs->next = new;
		new->prev = g_lines.curs;
		g_lines.curs = g_lines.curs->next;
	}
	g_lines.i++;
	g_lines.len++;
	return (true);
}

void						resert_curs(size_t len_path)
{
	size_t					l_total;
	int						loop;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) != NULL)
	{
		put_cmd_term("rc");
		put_cmd_term("cd");
		l_total = len_path + g_lines.len;
		g_lines.y = (l_total % sh->win.ws_col) == 1 ? g_lines.y + 1 : g_lines.y;
	}
}

int							put_end_line(char c)
{
	int						loop;
	t_entry					*curs;

	curs = (g_lines.curs != NULL) ? g_lines.curs->next : g_lines.line;
	if (put_cmd_term("cd") == ERROR)
		return (ERROR);
	loop = 0;
	if (c != '\n')
		ft_putchar(c);
	while (curs != NULL)
	{
		ft_putchar(curs->c);
		loop++;
		curs = curs->next;
	}
	while (loop-- > 0)
		if (put_cmd_term("le") == ERROR)
			return (false);
	if (c == '\n')
		ft_putchar('\n');
	return (true);
}

int							get_line_cmd(void)
{
	char					c;
	size_t					len_path;
	t_entry					*entry;
	t_entry					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	print_prompt();
	while (1)
	{
		if((c = get_char_keyboard()) != KEY_IGNORE)
			if (add_c_to_line(c) == ERROR)
				return (ERROR);
		if (c != KEY_IGNORE && c != ERROR)
			if (put_end_line(c) == ERROR)
				return (ERROR);
		if (c == '\n')
			sh->pos = 0;
		if (c == ERROR || c == '\n')
			break ;
	}
	return (true);
}

int							insert_word_in_g_line(char *word)
{
	unsigned int			i;
	t_21sh					*sh;

	if (word == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	i = 0;
	sh->pos_prev = sh->pos;
	while (word[i] != '\0' && word[i] != '\n')
		if (add_c_to_line(word[i++]) == ERROR)
			return (ERROR);
	i += sh->len_prompt;
	sh->pos = i / sh->win.ws_col;
	return (true);
}

void						del_g_lines(void)
{
	t_entry					*curs;
	t_entry					*mem;

	curs = g_lines.line;
	while (curs != NULL)
	{
		mem = curs->next;
		ft_memdel((void**)&curs);
		curs = mem;
	}
	ft_bzero(&g_lines, sizeof(g_lines));
}

char						*make_tab(void)
{
	char					*line;
	size_t					i;
	t_entry					*curs;

	if (g_lines.len <= 0)
		return (ft_memalloc(sizeof(*line)));
	if ((line = ft_memalloc(sizeof(*line) * (g_lines.len + 1))) == NULL)
		return (NULL);
	i = 0;
	curs = g_lines.line;
	while (curs != NULL)
	{
		line[i++] = curs->c;
		curs = curs->next;
	}
	del_g_lines();
	return (line);
}

char						*get_line_entree(void)
{
	if (get_line_cmd() == ERROR)
		return (NULL);
	return (make_tab());
}

int							my_out_put(int c)
{
	ft_putchar(c);
	return (1);
}
