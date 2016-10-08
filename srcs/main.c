/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:57:00 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 10:24:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/21sh.h"

void						put_path(char **tab_path)
{
	int						i;

	i = 0;
	while (tab_path[i] != NULL)
		ft_putendl(tab_path[i++]);
}

int							main(int argc, char **argv, char **env)
{
	t_21sh					*sh;

	if ((sh = init_21sh(env)) == NULL)
	{
		ft_putendl("Erreur initialisation 21sh");
		return ERROR;
	}
	put_path(sh->path);
	ft_putendl("ok");
	del_21sh();
	return (0);
}
