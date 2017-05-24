/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:55:25 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/24 17:56:25 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char						*ft_trim(char *str)
{
	size_t					start;
	size_t					end;

	start = 0;
	while (ft_isspace(str[start]))
		start++;
	end = ft_strlen(&str[start]);
	while (ft_isspace(str[start + end - 1]))
		if (end-- == 0)
			break ;
	return ((end > 0) ? ft_strndup(&str[start], end) : ft_strdup(""));
}
