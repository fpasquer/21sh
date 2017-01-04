/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:17:26 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/04 22:20:23 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_add_to_array(char *str, char **list)
{
	char		**new_list;
	int			len_list;
	int			i;

	new_list = NULL;
	if (ft_strlen(str) == 0)
		return (list);
	len_list = len_y(list);
	i = 0;
	if ((new_list = (char**)malloc(sizeof(char*) * (len_list + 2))) == NULL)
		return (NULL);
	if (len_list > 0)
	{
		while (list[i])
		{
			new_list[i] = list[i];
			i++;
		}
	}
	new_list[i++] = str;
	new_list[i] = NULL;
	if (list)
		free(list);
	return (new_list);
}
