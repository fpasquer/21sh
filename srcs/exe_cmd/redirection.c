/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:36:23 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/24 17:37:16 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

t_redirect_selec	g_redirect_selec[] = {
	{2, read_funct},
	{3, put_heredoc},
	{4, write_funct},
	{5, d_write_funct},
	{0, NULL}
};

int					redirecting(t_cmd *redirect, int index, int tgt_fd, int i)
{
	int				r;

	r = 0;
	if (redirect)
	{
		while (index != 0 && g_redirect_selec[i].p)
		{
			if (g_redirect_selec[i].num == index)
			{
				if (g_redirect_selec[i].p(redirect, tgt_fd) != 0)
					return (1);
			}
			i++;
		}
		if (redirect->cmd != 0)
			r = redirecting(redirect->left, redirect->cmd, redirect->tgt_fd, 0);
	}
	return (r);
}
