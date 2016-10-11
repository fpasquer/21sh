/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 14:46:02 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/11 14:52:24 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

void						key_exit(void)
{
	ft_putendl(COLOR_LINE);
	ft_putstr("exit");
	ft_putendl(RESET_COLOR);
	del_21sh();
	exit(0);
}
