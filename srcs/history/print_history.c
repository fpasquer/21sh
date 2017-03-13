/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:49:57 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/13 15:36:38 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#define NONE 0

/*static bool					at_add_history(char *line)
{
	int						i;
	bool					ret;

	if (line == NULL)
		return (false);
	if (line[0] == '\n')
		return (true);
	i = 0;
	ret = false;
	while (line[i] != '\0')
		ret = (ft_isspace(line[i++]) == true) ? ret : true;
	return (ret);
}

static size_t				get_y_line(size_t len_line)
{
	size_t					y;
	t_21sh					*sh;

	y = 0;
	if ((sh = get_21sh(NULL)) != NULL)
	{
		if (sh->win.ws_col == 0)
			return (0);
		len_line -= len_line % sh->win.ws_col;
		y = len_line / sh->win.ws_col;
	}
	return (y);
}*/

int							print_history(void)
{
	int						i;
	t_history				*curs;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	curs = sh->hist;
	i = 0;
	while (curs != NULL)
	{
		ft_putnbr_fd(i++, STDOUT_FILENO);
		ft_putstr_fd("  ", STDOUT_FILENO);
		ft_putendl_fd(curs->line, STDOUT_FILENO);
		curs = curs->next;
	}
	return (true);
}
