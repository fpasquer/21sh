/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_signaux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:23:46 by fpasquer          #+#    #+#             */
/*   Updated: 2016/12/23 22:14:22 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

void						resize_win(int val)
{
	t_21sh					*sh;

	val = val + 0; //voir avec flo
	if ((sh = get_21sh(NULL)) != NULL)
		ioctl(0, TIOCGWINSZ, &sh->win);
}

void						ctrl_d(int val)
{
	val = val + 0; //voir avec flo
	del_21sh();
	exit(EXIT_SUCCESS);
}
