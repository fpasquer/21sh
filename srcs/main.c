/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:57:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/11/01 13:43:05 by fpasquer         ###   ########.fr       */
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
		signal(SIGWINCH, resize_win);
		loop_shell();
		ft_putendl("Erreur 21 sh");
		//print_dico();
		//print_all_bin();
		//print_history();
		//del_21sh();
	}
	return (EXIT_SUCCESS);
}
