/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:42:53 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/23 15:35:41 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

int							main(int argc, char **argv, char **environ)
{
	t_21sh					*sh;


																				debug = fopen("debug", "w+");
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
	argc = 0;
	argv = NULL;
}
