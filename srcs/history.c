/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 19:55:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/11 21:42:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

int							add_history(t_histoy **hist, char **line)
{
	t_histoy				*new;
	t_histoy				*curs;

	if (hist == NULL || line == NULL || *line == NULL)
		return (ERROR);
	if ((new = ft_memalloc(sizeof(*new))) == NULL)
		return (ERROR);
	new->line = *line;
	if ((curs = *hist) == NULL)
		*hist = new;
	else
	{
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
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
	if ((sh->hist = ft_memalloc(sizeof(*sh->hist))) == NULL)
		return (ERROR);
	if ((fd = ft_fopen(HISTORY, "r+")) <= 0)
		return (ERROR);
	while ((ret = get_next_line(fd, &line)) > 0)
		if (add_history(&sh->hist, &line) == ERROR)
			return (ERROR);
	if (close(fd) != 0)
		return (ERROR);
	for (t_histoy *curs = sh->hist; curs != NULL; curs = curs->next)
		printf("line = '%s'\n", curs->line);
	return (true);
}

int							del_hist(void)
{
	int						fd;
	t_histoy				*curs;
	t_histoy				*tmp;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((curs = sh->hist) == NULL)
		return (ERROR);
	if ((fd = ft_fopen(HISTORY, "w+")) <= 0)
		return (ERROR);
	while (curs != NULL)
	{
		if (curs->line != NULL)
		{
			ft_putendl(curs->line);
			ft_putendl_fd(curs->line, fd);
			ft_memdel((void**)&curs->line);
		}
		tmp = curs->next;
		ft_memdel((void**)&curs);
		curs = tmp;
	}
	if (close(fd) != 0)
		return (ERROR);
	return (true);
}
