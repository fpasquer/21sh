/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 13:31:58 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/09 08:13:52 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

static int					tri_ascii(char *a, char *b)
{
	unsigned int		i;

	i = 0;
	while (a[i] == (char)b[i] && a[i] != '\0' && b[i] != '\0')
		i++;
	if ((b[i] < a[i] && a[i] != '\0') || (b[i] == '\0' && a[i] != '\0'))
		return (0);
	return (1);
}

static int					tri_len(char *a, char *b)
{
	size_t					len_a;
	size_t					len_b;

	if (a == NULL || b == NULL)
		return (false);
	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	return ((len_b > len_a) ? true : false);
}

int							name_tri(void *node1, void *node2)
{
	t_bin					**tmp1;
	t_bin					**tmp2;

	tmp1 = node1;
	tmp2 = node2;
	return (tri_ascii((*tmp1)->name, (*tmp2)->name));
}


int							len_tri(void *node1, void *node2)
{
	t_bin					**tmp1;
	t_bin					**tmp2;

	tmp1 = node1;
	tmp2 = node2;
	return (tri_len((*tmp1)->name, (*tmp2)->name));
}
