/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:36:23 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/26 20:57:19 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

typedef struct		s_redirect_selec
{
	int				num;
	void			(*p)(t_cmd *redirect);
}					t_redirect_selec;

t_redirect_selec	g_redirect_selec[] = {
	{1, pipe_funct},
	{2, read_funct},
	{3, d_read_funct},
	{4, write_funct},
	{5, d_write_funct},
	{0, NULL}
};

void				redirecting(t_cmd *cmd, t_cmd *redirect, int index, int i)
{
	if (redirect)
	{
		while (index != 0 && g_redirect_selec[i].p)
		{
			if (g_redirect_selec[i].num == index)
			{
				g_redirect_selec[i].p(redirect);
				break ;
			}
			i++;
		}
		if (redirect->cmd != 0)
			redirecting(cmd, redirect->left, redirect->cmd, 0);
	}
}
