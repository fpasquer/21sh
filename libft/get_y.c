/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_y.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:59:41 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:59:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int				get_y(const char *s, char c)
{
	int				curseur;
	unsigned int	y;

	y = 0;
	if (s != NULL)
	{
		curseur = DEHORS;
		while (*s == c && *s != '\0')
			s++;
		while (*s != '\0')
		{
			if (*s == c)
				if (curseur == DEDANS)
					y++;
			curseur = (*s++ == c) ? DEHORS : DEDANS;
		}
		if (curseur == DEDANS)
			y++;
	}
	return (y);
}
