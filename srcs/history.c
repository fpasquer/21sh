/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 19:55:00 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/08 12:24:07 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>
#define QUOTE '\''
#define D_QUOTE '\"'
#define NONE 0

/*static bool					at_add_history(char *line)
{
	int						i;
	bool					ret;

	if (line == NULL)
		return (false);
	if (line[0] == '\n')
		return (true);
	i = 0;
	ret = false;
	while (line[i] != '\0')
		ret = (ft_isspace(line[i++]) == true) ? ret : true;
	return (ret);
}

static size_t				get_y_line(size_t len_line)
{
	size_t					y;
	t_21sh					*sh;

	y = 0;
	if ((sh = get_21sh(NULL)) != NULL)
	{
		if (sh->win.ws_col == 0)
			return (0);
		len_line -= len_line % sh->win.ws_col;
		y = len_line / sh->win.ws_col;
	}
	return (y);
}*/

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
		if ((new_line = ft_multijoin(3, curs->line,"\n" ,line)) == NULL)
			return (ERROR);
		if (curs->line != NULL)
			ft_memdel((void**)&curs->line);
		curs->line = new_line;
	}
	else
		return (add_history_new_line(hist, line));
	return(true);
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
		if ((fd = ft_fopen(HISTORY, "w+")) <=0)
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

int							print_history(void)
{
	int						i;
	t_history				*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	curs = sh->hist;
	i = 0;
	while (curs != NULL)
	{
		printf("%3d : \n\t%s\n", i++, curs->line);
		curs = curs->next;
	}
	return (true);
}

int							del_hist(void)
{
	int						fd;
	t_history				*tmp;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((fd = ft_fopen(HISTORY, "w+")) <= 0)
		return (ERROR);
	while (sh->hist != NULL && sh->hist->next != NULL)
		sh->hist = sh->hist->next;
	while (sh->hist != NULL)
	{
		tmp = sh->hist->prev;
		if (sh->hist->line != NULL)
		{
			ft_putstr_fd(sh->hist->line, fd);
			ft_memdel((void**)&sh->hist->line);
		}
		ft_memdel((void**)&sh->hist);
		sh->hist = tmp;
	}
	return ((close(fd) != 0) ? ERROR : true);
}
