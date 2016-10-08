/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:56:07 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 19:16:21 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/21sh.h"

static void					del_hash_bin(t_bin **link)
{
	t_bin					*tmp;
	t_bin					*curs;
	t_bin					*mem;

	if (link != NULL)
	{
		curs = *link;
		while (curs != NULL)
		{
			ft_memdel((void**)&curs->name);
			ft_memdel((void**)&curs->path);
			ft_memdel((void**)&curs->path_name);
			mem = curs;
			curs = curs->next;
			ft_memdel((void**)&mem);
		}
	}
}

int							del_bin(void)
{
	int						i;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	i = 0;
	while (i < SIZE_HASH)
		del_hash_bin(&sh->hash[i++]);
	return (true);
}
