/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_wout_spc_be.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:57:15 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:57:16 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlen_wout_spc_be(const char *s)
{
	unsigned int	len;
	unsigned int	mem;

	if (s == NULL)
		return (0);
	len = 0;
	mem = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	while (*s != '\0')
	{
		if (*s != ' ' && *s != '\t' && *s != '\n')
		{
			len += mem;
			mem = 0;
			len++;
		}
		else
			mem++;
		s++;
	}
	return (len);
}
