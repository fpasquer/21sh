/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:30:13 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:30:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

static void					del_hash_bin(t_bin **link)
{
	t_bin					*mem;

	if (link != NULL && *link != NULL)
		while (*link != NULL)
		{
			if ((*link)->name != NULL)
				ft_memdel((void**)&(*link)->name);
			if ((*link)->path != NULL)
				ft_memdel((void**)&(*link)->path);
			if ((*link)->path_name != NULL)
				ft_memdel((void**)&(*link)->path_name);
			mem = (*link)->next;
			if ((*link) != NULL)
				ft_memdel((void**)link);
			(*link) = mem;
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
		if (sh->hash[i++] != NULL)
			del_hash_bin(&sh->hash[i - 1]);
	return (true);
}
