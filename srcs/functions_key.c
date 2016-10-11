/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 14:46:02 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/11 16:10:03 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

void						key_exit(int val_exit)
{
	ft_putendl(COLOR_LINE);
	ft_putstr("exit");
	ft_putendl(RESET_COLOR);
	del_21sh();
	exit(val_exit);
}
