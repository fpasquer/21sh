/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:55:53 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:55:55 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char			*adr;
	unsigned int	i;

	adr = (char*)s;
	i = 0;
	while (adr[i] != '\0' && adr[i] != c)
		i++;
	return (adr[i] == c ? (char*)s + i : NULL);
}
