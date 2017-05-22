/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:40:19 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/22 17:33:35 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

static char			*selec_dup(t_line *c, t_entry *cpy_start, t_entry *cpy_end)
{
	char			*cpy;
	size_t			len;
	size_t			i;
	int				pos_neg;

	if (c == NULL || c->sel_start == NULL || c->sel_end == NULL)
		return (NULL);
	i = 0;
	pos_neg = c->lft_rgt < 0 ? -1 : 1;
	len = c->lft_rgt ? (c->lft_rgt * pos_neg) + 1 : 1;
	if ((cpy = ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (cpy_start != cpy_end)
	{
		cpy[i] = pos_neg < 0 ? cpy_end->c : cpy_start->c;
		i++;
		if (pos_neg < 0)
			cpy_end = cpy_end->next;
		else
			cpy_start = cpy_start->next;
	}
	cpy[i] = cpy_start->c;
	c->sel_end = NULL;
	return (cpy);
}

int					cpy_event(void)
{
	t_21sh			*sh;
	t_line			*c;

	if ((sh = get_21sh(NULL)) == NULL)
		return (false);
	if ((c = g_curs) == NULL || c->line == NULL)
		return (false);
	if ((c->sel_start == NULL && c->sel_end == NULL && c->line)
			|| (c->activity == false && c->line))
	{
		c->sel_start = c->curs ? c->curs->next : c->line;
		c->sel_end = c->curs ? c->curs->next : c->line;
	}
	if (sh->cpy_tmp)
		ft_memdel((void**)&sh->cpy_tmp);
	if ((sh->cpy_tmp = selec_dup(c, c->sel_start, c->sel_end)) == NULL)
		return (false);
	return (true);
}

int					cut_event(void)
{
	t_21sh			*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL)
		return (false);
	if (cpy_event() == false || del_selec() == false)
		return (reset_selec(false));
	return (reset_selec(true));
}

int					past_event(void)
{
	t_21sh			*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL || sh->cpy_tmp == NULL)
		return (false);
	if (place_curs() == ERROR
			|| insert_word_in_g_line(sh->cpy_tmp, &g_curs) == ERROR)
		return (false);
	return (true);
}
