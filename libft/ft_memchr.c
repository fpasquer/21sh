/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:52:45 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:52:46 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem_s;
	unsigned int	i;

	i = 0;
	mem_s = (unsigned char *)s;
	while (i < n)
		if (mem_s[i++] == (unsigned char)c)
			return (&mem_s[--i]);
	return (NULL);
}
