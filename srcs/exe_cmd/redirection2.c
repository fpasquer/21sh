/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:55:56 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/09 01:38:16 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

void				read_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		if ((redirect->fd = ft_fopen(redirect->arg[0], "r")) >= 0)
			dup2(redirect->fd, tgt_fd);
		else
		{
			ft_putstr_fd("error :", STDERR_FILENO);
			ft_putstr_fd(redirect->arg[0], STDERR_FILENO);
			ft_putendl_fd(": permission denied", STDERR_FILENO);
		}
	}
}

void				d_read_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		tgt_fd = STDIN_FILENO;
	}
	else
		ft_putendl_fd("syntax error unexpected token `newline'", STDERR_FILENO);
}

void				write_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		if ((redirect->fd = ft_fopen(redirect->arg[0], "w+")) >= 0)
			dup2(redirect->fd, tgt_fd);
		else
		{
			ft_putstr_fd("error :", STDERR_FILENO);
			ft_putstr_fd(redirect->arg[0], STDERR_FILENO);
			ft_putendl_fd(": permission denied", STDERR_FILENO);
		}
	}
}

void				d_write_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		if ((redirect->fd = ft_fopen(redirect->arg[0], "a")) >= 0)
			dup2(redirect->fd, tgt_fd);
		else
		{
			ft_putstr_fd("error :", STDERR_FILENO);
			ft_putstr_fd(redirect->arg[0], STDERR_FILENO);
			ft_putendl_fd(": permission denied", STDERR_FILENO);
		}
	}
}
