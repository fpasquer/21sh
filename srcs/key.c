/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 10:58:55 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/13 16:38:25 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"

#define KEY_IGNORE -2

static t_line				*add_new_line(t_line **lst, char *line,
		unsigned int i)
{
	t_line					*new;
	t_line					*curs;

	if ((new = ft_memalloc(sizeof(*new))) == NULL || lst == NULL ||
			line == NULL)
		return (NULL);
	/*if (line[0] == '\n' || line[0] == '\0')
		return (*lst);*/
	if (ft_strncpy(new->line, line, i) == NULL)
		return (NULL);
	new->i = i;
	if ((curs = *lst) == NULL)
		*lst = new;
	else
	{
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return (*lst);
}

static char					cmd_keyboard(char b[SIZE_BUFF])
{
	if (ESC)
		key_exit(EXIT_SUCCESS);
	else if (F1)
		key_del_hist();
	else if (F2)
		print_history();
	else if (TAB)
		;
	else if (ARROW_UP)
		print_history_up();
	else if (ARROW_DOWN)
		print_history_down();
	else if (ARROW_RIGHT)
		;
	else if (ARROW_LEFT)
		;
	else if (DEL)
		;
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

static t_line				*get_line(void)
{
	char					c;
	unsigned				i;

	c = 0;
	while (c != '\n' && c != EOF)
	{
		i = 0;
		ft_bzero(g_line, sizeof(g_line));
		while (i < MAX_LEN_LINE)
		{
			if ((c = get_char_keyboard()) != KEY_IGNORE)
				ft_putchar(c);
			if (c == '\n' || c == EOF)
				break;
			if (c != KEY_IGNORE)
				g_line[i++] = c;
		}
		if ((g_lines = add_new_line(&g_lines, g_line, i)) == NULL)
			return (NULL);
	}
	return (g_lines);
}

static int					len_tab(t_line *lines)
{
	int						len_total;
	t_line					*curs;

	if (lines == NULL)
		return (-1);
	curs = lines;
	len_total = 0;
	while (curs != NULL)
	{
		len_total += curs->i;
		curs = curs->next;
	}
	return (len_total);
}

static char					*make_tab(t_line *lines)
{
	char					*line;
	int						len_total;
	t_line					*curs;

	if (lines == NULL || lines->line[0] == '\0')
		return (ft_memalloc(sizeof(*line)));
	if ((len_total = len_tab(lines)) < 0)
		return (NULL);
	if ((line = ft_memalloc(sizeof(*line) * (len_total + 1))) == NULL)
		return (NULL);
	curs = lines;
	while (curs != NULL)
	{
		if ((ft_strncat(line, curs->line, curs->i)) == NULL)
			return (NULL);
		curs = curs->next;
	}
	return (line);
}

void						del_lines(void)
{
	t_line					*tmp;

	while (g_lines != NULL)
	{
		tmp = g_lines->next;
		ft_memdel((void**)&g_lines);
		g_lines = tmp;
	}
}

char						*get_line_entree(void)
{
	char					*line;

	line = NULL;
	g_lines = get_line();
	line = make_tab(g_lines);
	del_lines();
	return (line);
}

int							my_out_put(int c)
{
	ft_putchar(c);
	return (1);
}