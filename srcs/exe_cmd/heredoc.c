/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:01:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/10 19:29:24 by fcapocci         ###   ########.fr       */
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
	if (token != NULL)
		return (0);
	return (0);
}
