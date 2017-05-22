/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:59:00 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:59:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char			*new_s;
	unsigned int	i;

	new_s = NULL;
	if (start <= ft_strlen(s))
	{
		if ((new_s = (char*)ft_memalloc(sizeof(*new_s) * len + 1)) == NULL)
			return (NULL);
		i = 0;
		while (s[start + i] != '\0' && i < len)
		{
			new_s[i] = s[start + i];
			i++;
		}
		new_s[i] = '\0';
	}
	return (new_s);
}
