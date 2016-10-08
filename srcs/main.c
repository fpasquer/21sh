/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:57:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 17:20:36 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/21sh.h"

int							main(void)
{
	t_21sh					*sh;

	if ((sh = init_21sh()) == NULL)
	{
		ft_putendl("Erreur initialisation 21sh");
		return (ERROR);
	}
	if (sh->pwd != NULL)
		ft_putendl(sh->pwd);
	ft_putendl("ok");
	del_21sh();
	return (EXIT_SUCCESS);
}
