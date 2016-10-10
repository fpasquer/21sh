/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:57:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/10 16:06:58 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include <stdio.h>

int							main(void)
{
	int						loop_max;
	t_21sh					*sh;

	if ((sh = init_21sh()) == NULL)
		ft_putendl("Erreur initialisation 21sh");
	else
	{
		//loop_shell();
		if (builtin_env("env           -i       -u                     dskgf     sdgdf") == ERROR)
			ft_putendl("Erreur");
		del_21sh();
	}
	return (EXIT_SUCCESS);
}
