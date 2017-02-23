/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:30:41 by fpasquer          #+#    #+#             */
/*   Updated: 2017/02/23 22:50:47 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../../incs/shell_21sh.h"

static int				loop_print_history(t_history *tmp, int nb_cmd_history)
{
	char			*str;
	unsigned int	i;
	unsigned		decal;
	size_t			len_nb;
	size_t			len_print;

	i = 1;
	len_nb = ft_nblen(nb_cmd_history) + 3;
	if ((str = ft_memalloc(sizeof(char) * len_nb)) == NULL)
		return (ERROR);
	ft_memset((void**)str, ' ', (len_print = len_nb - 1));
	decal = 10;
	while (tmp != NULL)
	{
		write(STDOUT_FILENO, str, len_print);
		ft_putnbr_fd(i, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
		ft_putendl_fd(tmp->line, STDOUT_FILENO);
		tmp = tmp->prev;
		len_print = (++i % decal == 0) ? len_print - 1 : len_print;
		decal = (i - 1 == decal) ? decal * 10 : decal;
	}
	ft_memdel((void**)&str);
	return (true);
}

int					option_none(int offset)
{
	unsigned int	i;
	t_21sh			*sh;
	t_history		*tmp;

	offset = (int)offset;
	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	i = 0;
	if ((tmp = sh->hist) != NULL)
	{
		while (tmp != NULL && tmp->next != NULL)
		{
			i++;
			tmp = tmp->next;
		}
		loop_print_history(tmp, i);
	}
	return (i == 0 ? false : true);
}

int					option_clear(int offset)
{
	int				i;
	t_21sh			*sh;
	t_history		*tmp;

	if ((sh = get_21sh(NULL)) == NULL || offset <= 0)
		return (offset <= 0 ? false : ERROR);
	if ((tmp = sh->hist) != NULL && (i = 0) == 0)
	{
		while (tmp != NULL && tmp->next != NULL)
			tmp = tmp->next;
		while (tmp != NULL && ++i < offset)
			tmp = tmp->prev;
		if (i == offset)
		{
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			ft_memdel((void**)&tmp);
			return (true);
		}
	}
	return (false);
}

int					option_append(int offset)
{
	offset = (int)offset;
	return (true);
}

int					option_nappend(int offset)
{
	offset = (int)offset;
	return (true);
}

int					option_delete(int offset)
{
	if (offset <= 0)
		return (ERROR);
	return (true);
}
