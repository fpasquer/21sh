/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:40:19 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/25 23:17:20 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

static char			*selec_dup(t_line *c)
{
	char			*cpy;
	size_t			len;

	if (c == NULL)
		return (NULL);
	len = (c->lft_rgt * 1) + 1;
	if ((ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (c->sel_start != c->sel_end)
	{
	}
	return (cpy);
}

int					cpy_event(void)
{
	t_21sh			*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL)
		return (false);
	if (sh->cpy_tmp)
		ft_memdel((void**)&sh->cpy_tmp);
	if ((sh->cpy_tmp = selec_dup(g_curs)) == NULL)
		return (reset_selec(false));
	reset_selec(true);
	return (true);
}

int					cut_event(void)
{
	t_21sh			*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL)
		return (false);
	cpy_event();
	del_selec();
	return (true);
}

int					past_event(void)
{
	t_21sh			*sh;

	if ((sh = get_21sh(NULL)) == NULL || g_curs == NULL)
		return (false);
	return (true);
}
