/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:52:28 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:52:30 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t n)
{
	void		*variable;

	if ((variable = malloc(n)) == NULL)
		return (NULL);
	ft_bzero(variable, n);
	return (variable);
}
