/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:31:09 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/18 23:30:00 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"

static int			search_line_in_history(char *line)
{
	t_21sh			*sh;
	t_history		*curs;
	char			*res;

	if ((sh = get_21sh(NULL)) == NULL || (curs = sh->hist) == NULL)
		return (false);
	res = NULL;
	while (curs)
	{
		if (!ft_strncmp(line, curs->line, ft_strlen(line)))
		{
			res = curs->line;
			fprintf(debug, "%s\n", curs->line);
			break ;
		}
		curs = curs->next;
	}
	insert_word_in_g_line(res ? res : "", &g_curs);
	return (true);
}

int					search_history(void)
{
	char			*srch_line;
	int				ret;

	srch_line = get_line_entree(true);
	g_lines = ft_memalloc(sizeof(t_line));
	g_curs = g_lines;
	if (srch_line == NULL)
		return (false);
	ret = search_line_in_history(srch_line);
	ft_memdel((void**)&srch_line);
	return (ret);
}
