/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:36:23 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/22 17:21:16 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

typedef struct		s_redirect_selec
{
	int				num;
	int				(*p)(t_21sh *sh);
}					t_redirect_selec;

t_redirect_selec	g_redirect_selec[] = {
	//{1, pipe_funct}
	//{2, <_funct}
	//{3, <<_funct}
	//{4, >_funct}
	//{5, >>_funct}
};

void				redirecting(t_cmd *cmd, t_cmd *redirect, int i)
{
	while (g_redirect_selec[i].num != cmd->cmd)
	{
		if (g_redirect_selec[i].num == cmd->cmd)
		{
			g_redirect_selec[i].p(NULL);
		}
		i++;
	}
	if (redirect->cmd != 0)
		redirecting(cmd, redirect->left, 0);
}
