/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 04:49:01 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/19 11:31:58 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void				scop(char *line, int *i, int *size)
{
	char			selec;
	int				dup_i;
	int				dup_size;

	dup_i = (*i) + 1;
	dup_size = (*size) + 1;
	selec = line[*i];
	while (line[dup_i] && line[dup_i] != selec)
	{
		dup_size++;
		dup_i++;
	}
	if (dup_i < ft_strlen(line))
	{
		*size = dup_size;
		*i = dup_i;
	}
	(*size)++;
	(*i)++;
}
