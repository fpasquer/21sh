/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:30:27 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/30 19:08:31 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

static int					add_new_sort_bin(t_bin **n)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || n == NULL || *n == NULL)
		return (ERROR);
	if ((*n)->i_sort > SIZE_DICO - 1)
		return (ERROR);
	if (sh->dico[(*n)->i_sort] != NULL)
		(*n)->n_dico = sh->dico[(*n)->i_sort];
	sh->dico[(*n)->i_sort] = (*n);
	return (true);
}

int							save_dico(t_bin **n)
{
	if (n == NULL || *n == NULL || SIZE_DICO < 27)
		return (ERROR);
	if ((*n)->name == NULL || (*n)->name[0] == '\0')
		return (ERROR);
	if ((*n)->name[0] >= 'a' && (*n)->name[0] <= 'z')
		(*n)->i_sort = (*n)->name[0] - 'a';
	else if ((*n)->name[0] >= 'A' && (*n)->name[0] <= 'Z')
		(*n)->i_sort = (*n)->name[0] - 'A';
	else
		(*n)->i_sort = SIZE_DICO - 1;
	return (add_new_sort_bin(n));
}
