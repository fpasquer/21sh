/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 20:38:33 by fpasquer          #+#    #+#             */
/*   Updated: 2016/12/29 16:32:25 by fcapocci         ###   ########.fr       */
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

void						print_dico2(t_bin *lst)
{
	while (lst != NULL)
	{
		ft_putendl(lst->name);
		lst = lst->n_dico;
	}
	ft_putchar('\n');
}

void						print_dico(void)
{
	int						i;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) != NULL)
	{
		i = 0;
		while (i < SIZE_DICO)
			print_dico2(sh->dico[i++]);
	}
}
