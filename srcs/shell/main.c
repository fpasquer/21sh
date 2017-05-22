/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:42:53 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/22 20:58:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

int							main(int argc, char **environ)
{
	t_21sh					*sh;

	argc = argc + 1;
	if ((sh = init_21sh(environ)) == NULL)
		ft_putendl("Erreur initialisation 21sh");
	else
	{
		sig_manager();
		signal(SIGWINCH, resize_win);
		loop_shell();
		ft_putendl("Erreur 21 sh");
	}
	return (EXIT_SUCCESS);
}
