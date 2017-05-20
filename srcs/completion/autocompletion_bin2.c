/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_bin2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 19:26:20 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:26:24 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static int					is_end_loop(t_entry *c)
{
	if (c == NULL || c->c == ' ' || c->c == ';')
		return (false);
	return (true);
}

char						*get_begin_bin(t_entry *c)
{
	char					*begin;
	size_t					len;
	size_t					mem_len;
	t_entry					*curs;

	if ((curs = c) == NULL)
		return (NULL);
	len = 0;
	while (is_end_loop(curs))
	{
		len++;
		curs = curs->prev;
	}
	if (len == 0)
		return (NULL);
	if ((begin = ft_memalloc(sizeof(begin) * (len + 1))) == NULL)
		return (NULL);
	mem_len = len;
	while (is_end_loop(c))
	{
		begin[--len] = c->c;
		c = c->prev;
	}
	return (del_car_begin_in_g_line(mem_len) == ERROR ? NULL : begin);
}
