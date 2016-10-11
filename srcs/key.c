/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 10:58:55 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/11 14:45:17 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"

static t_line				*add_new_line(t_line **lst, char *line,
		unsigned int i)
{
	t_line					*new;
	t_line					*curs;

	if ((new = ft_memalloc(sizeof(*new))) == NULL || lst == NULL ||
			line == NULL)
		return (NULL);
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
		key_exit();
	return (b[0]);
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
	char					line[MAX_LEN_LINE + 1];
	unsigned				i;
	t_line					*lst;

	lst = NULL;
	c = get_char_keyboard();
	while (c != '\n' && c != EOF)
	{
		i = 0;
		ft_bzero(line, sizeof(line));
		while (i < MAX_LEN_LINE)
		{
			ft_putchar(c);
			if (c == '\n' || c == EOF)
				break;
			line[i++] = c;
			c = get_char_keyboard();
		}
		if ((lst = add_new_line(&lst, line, i)) == NULL)
			return (NULL);
	}
	return (lst);
}

static void					del_lines(t_line **lines)
{
	t_line					*curs;
	t_line					*tmp;

	if (lines != NULL && (curs = *lines) != NULL)
		while (curs != NULL)
		{
			tmp = curs->next;
			ft_memdel((void**)&curs);
			curs = tmp;
		}
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

	if (lines == NULL)
		return (NULL);
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

char						*get_line_entree(void)
{
	char					*line;
	t_line					*lines;
	t_line					*curs;

	if ((lines = get_line()) == NULL)
		return (NULL);
	line = make_tab(lines);
	del_lines(&lines);
	return (line);
}
