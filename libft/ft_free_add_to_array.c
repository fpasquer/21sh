/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_add_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 09:00:20 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/24 09:03:40 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool						ft_free_add_to_array(char **array)
{
	if (array == NULL)
		return (false);
	ft_memdel((void**)&array);
	return (true);
}
