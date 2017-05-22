/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:49:23 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:49:24 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							count_char(char *line, char c)
{
	unsigned int			i;
	int						ret;

	i = 0;
	ret = 0;
	if (line != NULL)
		while (line[i] != '\0')
			ret = line[i++] == c ? ret + 1 : ret;
	return (ret);
}
