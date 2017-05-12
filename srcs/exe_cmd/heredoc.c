/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:01:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/11 19:46:58 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

static char				get_char(void)
{
	char				b[SIZE_BUFF];

	if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0)
		return (ERROR);
	if ((b[0] >= 32 && b[0] <= 126) || ENTER)
		return (b[0]);
	return (0);
}


int						heredoc(char *token)
{
	char				c;
	char				*str;

	str = NULL;
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL )
		return (1);
	g_curs = g_lines;
	while (42)
	{
		c = get_char();
		if (c == '\n')
			str = make_tab();
		if (str && ft_strequ(str, token))
			break ;
	}
	del_g_lines();
	return (0);
}
