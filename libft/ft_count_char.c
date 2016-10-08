/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 23:00:25 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 21:55:30 by fpasquer         ###   ########.fr       */
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
