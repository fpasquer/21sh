/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:57:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/10 19:42:12 by fpasquer         ###   ########.fr       */
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
		char entree[] = "env   -u PAGER    pwd=jkhdskfhasdk";
		if (builtin_env(entree) == ERROR)
			ft_putendl("Erreur");
		del_21sh();
	}
	return (EXIT_SUCCESS);
}
