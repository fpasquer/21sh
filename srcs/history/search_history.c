/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:31:09 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/22 16:39:07 by fcapocci         ###   ########.fr       */
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
		if (strstr(curs->line, line))
		{
			res = curs->line;
			break ;
		}
		curs = curs->next;
	}
	return (insert_word_in_g_line(res ? res : line, &g_curs));
}

int					search_history(void)
{
	char			*srch_line;
	int				ret;

	place_curs();
	put_cmd_term("cd");
	g_curs->h_srch = true;
	print_prompt();
	g_curs->h_srch = false;
	srch_line = get_line_entree(true);
	g_lines = ft_memalloc(sizeof(t_line));
	g_curs = g_lines;
	if (srch_line == NULL || !strcmp(srch_line, ""))
		return (false);
	ret = search_line_in_history(srch_line);
	ft_memdel((void**)&srch_line);
	return (ret);
}
