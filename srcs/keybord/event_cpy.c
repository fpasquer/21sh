/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:40:19 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/27 20:23:48 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

static char			*selec_dup(t_line *c)
{
	char			*cpy;
	size_t			len;
	size_t			i;
	int				pos_neg;

	if (c == NULL)
		return (NULL);
	i = 0;
	pos_neg = c->lft_rgt < 0 ? -1 : 1;
	len = c->lft_rgt ? (c->lft_rgt * pos_neg) + 1 : 1;
	if ((cpy = ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (c->sel_start != c->sel_end)
	{
		cpy[i] = pos_neg < 0 ? c->sel_end->c : c->sel_start->c;
		i++;
		if (pos_neg < 0)
			c->sel_end = c->sel_end->next;
		else
			c->sel_start = c->sel_start->next;
	}
	cpy[i] = c->sel_start->c;
	return (cpy);
}

int					cpy_event(void)
{
	t_21sh			*sh;
	t_line			*c;

	if ((sh = get_21sh(NULL)) == NULL)
		return (false);
	if ((c = g_curs) == NULL)
		return (false);
	if (c->sel_start == NULL && c->curs && c->curs->next)
	{
		c->sel_start = c->curs->next;
		c->sel_end = c->curs->next;
	}
	if (c->sel_start == NULL || c->sel_end == NULL)
		return (false);
	if (sh->cpy_tmp)
		ft_memdel((void**)&sh->cpy_tmp);
	if ((sh->cpy_tmp = selec_dup(c)) == NULL)
		return (reset_selec(false));
	return (reset_selec(true));
}

int					cut_event(void)
{
	t_21sh			*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL)
		return (false);
	cpy_event();
	//del_selec();
	return (true);
}

int					past_event(void)
{
	t_21sh			*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL || sh->cpy_tmp == NULL)
		return (false);
	if (place_curs () == ERROR
			|| insert_word_in_g_line(sh->cpy_tmp, &g_curs) == ERROR)
		return (false);
	return (true);
}
