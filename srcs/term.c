/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 08:26:41 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/12 19:15:07 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include <term.h>

int							save_win_size(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (ioctl(0, TIOCGWINSZ, &sh->win) < 0)
		return (ERROR);
	return (true);
}

int							init_term(t_21sh **sh)
{
	if (sh == NULL || *sh == NULL)
		return (ERROR);
	if (tgetent(NULL, (*sh)->term_name) <= 0 || tcgetattr(0, &(*sh)->reset) < 0
			|| tcgetattr(0, &(*sh)->term_param) < 0)
		return (ERROR);
	(*sh)->term_param.c_lflag &= ~(ICANON);
	(*sh)->term_param.c_lflag &= ~(ECHO);
	(*sh)->term_param.c_lflag &= ~(ISIG);
	(*sh)->term_param.c_cc[VMIN] = 1;
	(*sh)->term_param.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &(*sh)->term_param) == -1)
		return (ERROR);
	return (save_win_size());
}