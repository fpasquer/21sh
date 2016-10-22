/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:36:23 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/22 19:50:07 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

typedef struct		s_redirect_selec
{
	int				num;
	int				(*p)(int index, t_cmd *redirect);
}					t_redirect_selec;

t_redirect_selec	g_redirect_selec[] = {
	//{1, pipe_funct}
	//{2, <_funct}
	//{3, <<_funct}
	//{4, >_funct}
	//{5, >>_funct}
};

static char			**add_tab(char ***tab1, char **tab2, int i)
{
	char		**new_tab;
	int			index1;
	int			index2;
	int			p;

	p = 0;
	index1 = len_y(*tab1);
	index2 = len_y(tab2);
	if ((new_tab = ft_memalloc(sizeof(new_tab) * (index1 + index2))) == NULL)
		return (*tab1);
	while ((*tab1)[p])
	{
		new_tab[p] = ft_strdup((*tab1)[p]);
		p++;
	}
	while (tab2[i])
	{
		new_tab[p] = ft_strdup(tab2[i]);
		p++;
		i++;
	}
	new_tab[p] = NULL;
	ft_free_strsplit(*tab1);
	return (new_tab);
}

void				redirecting(t_cmd *cmd, t_cmd *redirect, int index, int i)
{
	while (index != 0 && g_redirect_selec[i].num != index)
	{
		if (g_redirect_selec[i].num == index)
			g_redirect_selec[i].p(index, redirect);
		i++;
	}
	if (redirect->cmd != 0)
		redirecting(cmd, redirect->left, redirect->cmd, 0);
	if (redirect->arg && redirect->arg[1])
		cmd->arg = add_tab(&(cmd->arg), redirect->arg, 1);
}
