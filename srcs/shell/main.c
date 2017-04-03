/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 21:42:53 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/03 15:39:13 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

int							main(void)
{
	t_21sh					*sh;

	if ((sh = init_21sh()) == NULL)
		ft_putendl("Erreur initialisation 21sh");
	else
	{
		if ((debug = fopen("test.txt", "w+")) == NULL)
			return (EXIT_SUCCESS);
		sig_manager();
		signal(SIGWINCH, resize_win);
		loop_shell();
		ft_putendl("Erreur 21 sh");
	}
	return (EXIT_SUCCESS);
}
