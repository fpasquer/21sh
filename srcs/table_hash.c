/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:25:55 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 22:00:49 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

int							i_table_hash(char *name, int size_hash)
{
	unsigned int			i;
	unsigned long long int	somme_c;

	i = 0;
	somme_c = 0;
	if (name == NULL || size_hash <= 0)
		return (ERROR);
	while (name[i] != '\0')
		somme_c += name[i++];
	return ((int)somme_c % size_hash);
}
