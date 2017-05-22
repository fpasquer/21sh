/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:54:46 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/27 21:54:48 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_putendl_fd(const char *s, int fd)
{
	unsigned int	len;

	len = ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return (len + 1);
}
