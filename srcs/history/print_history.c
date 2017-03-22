/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:49:57 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/22 19:26:26 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#define NONE 0

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
