/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:27:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/24 16:27:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char							*ft_implode(char glue, char **list)
{
	char						*ret;
	char						cpy_glue[2];
	size_t						i;
	size_t						len;

	i = 0;
	len = 0;
	ret = NULL;
	ft_bzero(cpy_glue, sizeof(cpy_glue));
	cpy_glue[0] = glue;
	while (list != NULL && list[i] != NULL)
		len += ft_strlen(list[i++]);
	if (len > 0 && (ret = ft_memalloc(sizeof(*ret) * (len + i))) != NULL)
	{
		i = 0;
		while (list != NULL && list[i] != NULL)
		{
			if (i > 0)
				if (ft_strcat(ret, cpy_glue) == NULL)
					return (ret);
			if (ft_strcat(ret, list[i++]) == NULL)
				return (ret);
		}
	}
	return (ret);
}

