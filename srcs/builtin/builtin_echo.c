/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:06:16 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/11 19:14:10 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int				ft_echo(char *str, int fd)
{
	int			i;

	i = 0;
	if (str && str[i] != '\0')
	{
		while (str[i] && str[i] != '\0')
		{
			if (str[i] != '\"' && str[i] != '\\' && str[i] != '\'')
				ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	if (!FLAGS)
		ft_putchar_fd('\n', fd);
	return (0);
}
