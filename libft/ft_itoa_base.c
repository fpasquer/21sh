/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:51:43 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:51:44 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa_base(long long int nb, const unsigned int base)
{
	char						*tmp;
	char						*ret;
	unsigned long long int		nb_cpy;

	nb_cpy = (unsigned long long int)(nb < 0) ? nb * -1 : nb;
	if ((ret = ft_utoa_base(nb_cpy, base)) != NULL)
	{
		if (nb < 0 && base == 10)
		{
			if ((tmp = ft_strjoin("-", ret)) == NULL)
				return (NULL);
			ft_memdel((void**)&ret);
			ret = tmp;
		}
	}
	return (ret);
}
