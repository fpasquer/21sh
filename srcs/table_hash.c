/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:25:55 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/14 11:40:12 by fcapocci         ###   ########.fr       */
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

int							get_path_bin(char *name_bin, char **path_name)
{
	int						index;
	t_bin					*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || name_bin == NULL)
		return (ERROR);
	if ((index = i_table_hash(name_bin, SIZE_HASH)) >= 0 && index < SIZE_HASH)
	{
		curs = sh->hash[index];
		while (curs != NULL)
		{
			if (ft_strcmp(name_bin, curs->name) == 0)
			{
				*path_name = curs->path_name;
				return (true);
			}
			curs = curs->next;
		}
	}
	*path_name = NULL;
	return (false);
}
