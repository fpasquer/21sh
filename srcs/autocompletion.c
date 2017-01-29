/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:47:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/29 15:38:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static t_entry				*get_last_addr_c(void)
{
	t_line					*curs;
	t_entry					*c;

	if ((curs = g_curs) == NULL)
		return (NULL);
	c = curs->curs;
	while (c != NULL && c->next != NULL)
		c = c->next;
	while (c != NULL && c->c == ' ')
		c = c->prev;
	return (c);
}

static int					move_line_end(void)
{
	int						mem;

	mem = true;
	while (mem != false)
	{
		if ((mem = move_right()) == ERROR)
			return (ERROR);
	}
	return (true);
}

int							autocompletion(void)
{
	t_entry					*c;

	if (move_line_end() == ERROR || (c = get_last_addr_c()) == NULL)
																				{
																					fprintf(debug, "ici line %d\n", __LINE__);
		return ((g_curs == NULL) ? ERROR : false);
																				}
	if (c->c != ' ')
		return autocompletion_bin(c);
	return (true);
}
