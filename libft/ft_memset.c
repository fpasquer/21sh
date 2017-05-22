/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:53:39 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:53:40 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*mem;
	unsigned int	i;

	i = 0;
	mem = (unsigned char *)s;
	while (n)
	{
		mem[i++] = (unsigned char)c;
		n--;
	}
	return (s);
}
