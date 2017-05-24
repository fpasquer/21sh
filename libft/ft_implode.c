/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:27:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/24 16:43:45 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char							*ft_implode(char *glue, char **list)
{
	char						*ret;
	size_t						i;
	size_t						len;

	i = 0;
	len = 0;
	ret = NULL;
	if (list == NULL || glue == NULL)
		return (NULL);
	while (list[i] != NULL)
		len += ft_strlen(list[i++]);
	if (len > 0 && (ret = ft_memalloc(sizeof(*ret) *
			(len + ((i - 1) * ft_strlen(glue)) + 1))) != NULL)
	{
		i = 0;
		while (list[i] != NULL)
		{
			if (i > 0)
				if (ft_strcat(ret, glue) == NULL)
					return (ret);
			if (ft_strcat(ret, list[i++]) == NULL)
				return (ret);
		}
	}
	return (ret);
}
