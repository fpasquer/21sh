/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_del_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 11:24:58 by fpasquer          #+#    #+#             */
/*   Updated: 2017/02/08 11:33:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#define QUOTE '\''
#define D_QUOTE '\"'
#define NONE 0

static int					end_line(char *line)
{
	int						quote;
	unsigned int			i;

	if (line == NULL)
		return (ERROR);
	i = 0;
	quote = NONE;
	while (line[i++] != '\0')
		if (line[i - 1] == '\'' && (quote == NONE || quote == QUOTE))
			quote = (quote == NONE) ? QUOTE : NONE;
		else if (line[i - 1] == '\"' && (quote == NONE || quote == D_QUOTE))
			quote = (quote == NONE) ? D_QUOTE : NONE;
	return (quote);
}

static int					add_history_new_line(t_history **hist, char *line)
{
	t_history				*new;

	if (hist == NULL || *hist == NULL || line == NULL)
		return (ERROR);
	if ((new = ft_memalloc(sizeof(*new))) == NULL)
		return (ERROR);
	if ((new->line = ft_strdup(line)) == NULL)
		return (ERROR);
	(*hist)->prev = new;
	new->next = (*hist);
	(*hist) = new;
	return (true);
}

static int					add_history_line(t_history **hist, char *line)
{
	char					*new_line;
	int						quote_prev;
	t_history				*curs;

	if (hist == NULL || *hist == NULL || line == NULL || (curs = *hist) == NULL)
		return (ERROR);
	if ((quote_prev = end_line(curs->line)) != NONE)
	{
		if ((new_line = ft_multijoin(3, curs->line, "\n", line)) == NULL)
			return (ERROR);
		if (curs->line != NULL)
			ft_memdel((void**)&curs->line);
		curs->line = new_line;
	}
	else
		return (add_history_new_line(hist, line));
	return (true);
}

int							add_history(t_history **hist, char *line)
{
	t_history				*new;

	if (hist == NULL || line == NULL)
		return (ERROR);
	if (*hist == NULL)
	{
		if ((new = ft_memalloc(sizeof(*new))) == NULL)
			return (ERROR);
		if ((new->line = ft_strdup(line)) == NULL)
			return (ERROR);
		new->len = ft_strlen(new->line);
		(*hist) = new;
	}
	else
		return (add_history_line(hist, line));
	return (true);
}

int							init_history(void)
{
	char					*line;
	int						ret;
	int						fd;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((fd = ft_fopen(HISTORY, "r+")) <= 0)
		if ((fd = ft_fopen(HISTORY, "w+")) <= 0)
			return (ERROR);
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (add_history(&sh->hist, line) == ERROR)
			return (ERROR);
		ft_memdel((void**)&line);
	}
	if (close(fd) != 0)
		return (ERROR);
	return (true);
}
