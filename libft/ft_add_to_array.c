/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:48:00 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/24 08:54:12 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_add_to_array(char *str, char **list)
{
	char		**new;
	int			len_list;
	int			i;

	new = NULL;
	if (ft_strlen(str) == 0)
		return (list);
	len_list = len_y(list);
	i = 0;
	if ((new = (char**)ft_memalloc(sizeof(char*) * (len_list + 2))) == NULL)
		return (NULL);
	if (len_list > 0)
		while (list[i])
		{
			new[i] = list[i];
			i++;
		}
	new[i++] = str;
	new[i] = NULL;
	if (list)
		free(list);
	return (new);
}
