/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 11:32:19 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/08 11:33:40 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							del_hist(void)
{
	int						fd;
	t_history				*tmp;
	t_21sh					*sh;

	sh = get_21sh(NULL);
	if (sh == NULL || (fd = ft_fopen(HISTORY, "w+")) <= 0)
		return (ERROR);
	while (sh->hist != NULL && sh->hist->next != NULL)
		sh->hist = sh->hist->next;
	while (sh->hist != NULL)
	{
		tmp = sh->hist->prev;
		if (sh->hist->line != NULL)
		{
			if (ft_strchr(sh->hist->line, '\n') == NULL)
				ft_putendl_fd(sh->hist->line, fd);
			else
				ft_putstr_fd(sh->hist->line, fd);
			ft_memdel((void**)&sh->hist->line);
		}
		ft_memdel((void**)&sh->hist);
		sh->hist = tmp;
	}
	return ((close(fd) != 0) ? ERROR : true);
}
