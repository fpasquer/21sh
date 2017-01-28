/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 17:37:05 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/28 18:06:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static t_entry				*get_addr_last(void)
{
	t_entry					*c;
	t_line					*curs;

	if ((curs = g_curs) == NULL)
		return (NULL);
	c = curs->line;
	while (c != NULL && c->next != NULL)
		c = c->next;
	return (c == curs->line ? NULL : c);
}

int							autocompletion(void)
{
	t_entry					*last_c;

	if ((last_c = get_addr_last()) == NULL)
	{
																				fprintf(debug, "c = %pi line + %d\n", last_c, __LINE__);
		return (g_curs == NULL ? ERROR : false);
	}
																				fprintf(debug, "c = %pi line + %d\n", last_c, __LINE__);
	return (true);
}
