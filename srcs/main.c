/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:57:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 21:42:32 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/21sh.h"
#include <stdio.h>

int							main(void)
{
	int						loop_max;
	t_21sh					*sh;

	if ((sh = init_21sh()) == NULL)
		ft_putendl("Erreur initialisation 21sh");
	else
	{
		printf("PWD = %s\n", sh->pwd);
		printf("OLDPWD = %s\n", sh->old_pwd);
		printf("TERM = %s\n", sh->term_name);
		printf("HOME = %s\n", sh->home);
		printf("USER = %s\n", sh->user);
		printf("PATH = %s\n", sh->path);
		printf("SHLVL = %d\n", sh->sh_lvl);
		del_21sh();
	}
	return (EXIT_SUCCESS);
}
