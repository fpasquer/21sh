/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 04:49:01 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/19 06:14:30 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void				scop_1st(char *line, int *i, int *size)
{
	char			selec;
	int				dup_i;
	int				dup_size;

	dup_i = (*i) + 1;
	dup_size = (*size) + 1;
	selec = line[*i];
	while (dup_i < ft_strlen(line) && line[dup_i] != selec)
	{
		dup_i++;
		dup_size++;
	}
	if (dup_i > 0)
	{
		ft_putendl("ICI");
		(*i)++;
		(*size)++;
		return ;
	}
	else
	{
		ft_putendl("LA");
		*i = dup_i;
		*size = dup_size;
	}
}
