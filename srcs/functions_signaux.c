/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_signaux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:23:46 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/13 14:56:58 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

void						resize_win(int val)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) != NULL)
		ioctl(0, TIOCGWINSZ, &sh->win);
}

void						ctrl_d(int val)
{
	del_21sh();
	exit(EXIT_SUCCESS);
}
