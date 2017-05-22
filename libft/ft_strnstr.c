/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:58:26 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:58:28 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trouve_aiguille(const char *meule, const char *aiguille, size_t n)
{
	while (*meule == *aiguille && n-- && *meule != '\0')
	{
		meule++;
		if (*++aiguille == '\0')
			return (1);
	}
	return (0);
}

char		*ft_strnstr(const char *meule, const char *aiguille, size_t n)
{
	if (*aiguille == '\0')
		return ((char*)meule);
	while (*meule != '\0' && n--)
	{
		if (*meule == *aiguille)
			if (trouve_aiguille(meule, aiguille, n + 1))
				return ((char *)meule);
		meule++;
	}
	return (NULL);
}
