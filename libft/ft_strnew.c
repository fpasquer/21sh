/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:58:21 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:58:21 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char *s;

	if ((s = (char*)malloc(sizeof(*s) * size + 1)) == NULL)
		return (NULL);
	ft_memset(s, '\0', size + 1);
	return (s);
}
