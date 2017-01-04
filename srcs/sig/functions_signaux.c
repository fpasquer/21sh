/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_signaux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:30:40 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/04 14:30:41 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

void						resize_win(int val)
{
	t_21sh					*sh;

	val = val + 0;
	if ((sh = get_21sh(NULL)) != NULL)
		ioctl(0, TIOCGWINSZ, &sh->win);
}

void						ctrl_d(int val)
{
	val = val + 0;
	del_21sh();
	exit(EXIT_SUCCESS);
}
