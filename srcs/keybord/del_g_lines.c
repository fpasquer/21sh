/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_g_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:28:25 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/04 17:28:28 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"

static void					loop_del_g_lines(t_line **lines)
{
	t_entry					*curs;
	t_entry					*mem;

	if (lines == NULL || *lines == NULL)
		return ;
	curs = (*lines)->line;
	while (curs != NULL)
	{
		mem = curs->next;
		ft_memdel((void**)&curs);
		curs = mem;
	}
	ft_memdel((void**)lines);
}

static int					reset_g_curs(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL || g_lines == NULL)
		return (ERROR);
	ft_bzero(g_curs, sizeof(*g_curs));
	if (g_curs == g_lines)
	{
		g_curs->x = (sh->len_prompt - 1) % sh->win.ws_col;
		g_curs->x_i = (sh->len_prompt - 1) % sh->win.ws_col;
		g_curs->y = (sh->len_prompt - 1) / sh->win.ws_col;
		g_curs->y_i = (sh->len_prompt - 1) / sh->win.ws_col;
	}
	return (true);
}

int							change_value_g_curs_line(char *word)
{
	size_t					i;
	t_entry					*curs;
	t_entry					*mem;

	if (g_curs == NULL)
		return (false);
	if (place_curs() == ERROR)
		return (ERROR);
	curs = g_curs->line;
	while (curs != NULL)
	{
		mem = curs->next;
		ft_memdel((void**)&curs);
		curs = mem;
	}
	if (reset_g_curs() == ERROR)
		return (ERROR);
	i = 0;
	while (word[i++] != '\0')
		if (word[i - 1] != '\n' || (word[i - 1] == '\n' && word[i] != '\0'))
			if (add_c_to_line(word[i - 1], &g_curs) == ERROR)
				return (ERROR);
	return (true);
}

void						del_g_lines(void)
{
	t_line					*tmp;

	while (g_lines != NULL)
	{
		tmp = g_lines->next;
		loop_del_g_lines(&g_lines);
		g_lines = tmp;
	}
	g_curs = NULL;
}
