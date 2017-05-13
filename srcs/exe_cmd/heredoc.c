/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:01:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/13 23:45:11 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

#define KEY_IGNORE -2
#define PRINT_MAX 500

static int				add_c_to_tab(char str[], char c)
{
	if (*str && c == '\n')
		return (1);
	return (0);
}

int						heredoc(char *token)
{
	char				c;
	char				str[PRINT_MAX + 1];
	char				buff[PRINT_MAX + 1];
	char				tmp[PRINT_MAX + 1];

	ft_bzero(str, sizeof(str));
	ft_bzero(buff, sizeof(buff));
	ft_bzero(buff, sizeof(tmp));
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL )
		return (1);
	g_curs = g_lines;
	g_curs->h_srch = true;
	while (42)
	{
		c = get_char_keyboard();
		if (place_curs() == ERROR)
			break ;
		if (c != KEY_IGNORE && ft_isascii(c))
		{
			if (add_c_to_line(c, &g_curs) == ERROR)
				break ;
			if ((add_c_to_tab(str, c)) == 0)
				if (ft_strequ(str, token))
					break ;
		}
	}
	del_g_lines();
	return (0);
}
