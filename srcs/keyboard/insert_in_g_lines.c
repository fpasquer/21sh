/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_in_g_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:38:34 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/12 19:40:58 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#include <limits.h>

static int					check_save_y_x(t_line **lines)
{
	int						ret;

	if (lines == NULL || *lines == NULL)
		return (ERROR);
	(*lines)->i = ((*lines)->len == 0) ? 0 : (*lines)->i + 1;
	(*lines)->len++;
	ret = save_y_x_line(lines);
	return (ret);
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

int							add_c_to_line(char c, t_line **line)
{
	t_entry					*n;

	if (creat_new_line(line, c) == true)
		return (true);
	if ((n = ft_memalloc(sizeof(*n))) == NULL || line == NULL || *line == NULL)
		return (ERROR);
	n->c = c;
	if ((*line)->curs == NULL || (*line)->i == ULONG_MAX)
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
	return (check_save_y_x(line));
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
