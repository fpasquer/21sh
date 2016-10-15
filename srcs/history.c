/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 19:55:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/15 20:26:35 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>

static bool					at_add_history(char *line)
{
	int						i;
	bool					ret;

	if (line == NULL)
		return (false);
	i = 0;
	ret = false;
	while (line[i] != '\0')
		ret = (ft_isspace(line[i++]) == true) ? ret : true;
	return (ret);
}

int							add_history(t_history **hist, char **line)
{
	t_history				*new;
	t_history				*curs;

	if (hist == NULL || line == NULL || *line == NULL)
		return (ERROR);
	if (*line[0] != '\0' && *line[0] != '\0'  && at_add_history(*line) == true)
	{
		if ((new = ft_memalloc(sizeof(*new))) == NULL)
			return (ERROR);
		new->line = *line;
		if ((curs = *hist) != NULL)
		{
			new->next = (*hist);
			(*hist)->prev = new;
		}
		*hist = new;
	}
	else
		ft_memdel((void**)line);
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
		if (add_history(&sh->hist, &line) == ERROR)
			return (ERROR);
	if (close(fd) != 0)
		return (ERROR);
	return (true);
}

static int					loop_print(t_21sh *sh)
{
	char					**list;
	char					*ret;
	int						loop;
	t_history				*curs;

	curs = (sh == NULL) ? NULL : sh->hist;
	loop = 0;
	while (curs != NULL)
	{
		loop++;
		curs = curs->next;
	}
	if (loop == 0 || (list = ft_memalloc((sizeof(*list) * (loop + 1)))) == NULL)
		return ((loop == 0) ? false : ERROR);
	curs = sh->hist;
	loop = 0;
	while (curs != NULL)
	{
		list[loop++] = curs->line;
		curs = curs->next;
	}
	ret = print_list_term(sh, list, false);// a passer en false
	ft_memdel((void**)&list);
	return ((ret == NULL) ? false : true);
}

int							print_history(void)
{
	int						ret;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	ft_putendl(COLOR_LINE);
	ft_putstr("print_history");
	ft_putendl(RESET_COLOR);
	ret = loop_print(sh);
	if (ret == ERROR)
		ft_putendl("History error");
	else if (ret == false)
		ft_putendl("History empty");
	print_prompt();
	return (ret);
}

int							del_hist(void)
{
	int						fd;
	t_history				*curs;
	t_history				*tmp;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((fd = ft_fopen(HISTORY, "w+")) <= 0)
		return (ERROR);
	if (sh->hist == NULL)
		return (true);
	while (sh->hist->next != NULL)
		sh->hist = sh->hist->next;
	while (sh->hist != NULL)
	{
		tmp = sh->hist->prev;
		if (sh->hist->line != NULL)
		{
			ft_putendl_fd(sh->hist->line, fd);
			ft_memdel((void**)&sh->hist->line);
		}
		ft_memdel((void**)&sh->hist);
		sh->hist = tmp;
	}
	return ((close(fd) != 0) ? ERROR : true);
}
