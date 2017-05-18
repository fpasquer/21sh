/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:02:07 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/18 12:02:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>

void						print_g_line(void)
{
	char					cpy_word[SIZE_MEM + 1];
	int						i;
	t_entry					*curs;

	curs = g_lines->line;
	while (curs != NULL)
	{
		i = 0;
		ft_bzero(&cpy_word, sizeof(cpy_word));
		while (i < SIZE_MEM && curs != NULL)
		{
			cpy_word[i++] = curs->c;
			curs = curs->next;
		}
		ft_putstr(cpy_word);
	}
}
