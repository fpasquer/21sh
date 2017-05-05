/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:55:56 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/05 16:57:53 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

static void			msg_error(char *str)
{
	ft_putstr_fd("error :", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": permission denied", STDERR_FILENO);
}

void				read_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		if ((redirect->fd = ft_fopen(redirect->arg[0], "r")) >= 0)
			dup2(redirect->fd, tgt_fd);
		else
			msg_error(redirect->arg[0]);
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
	char			*ptr;

	ptr = redirect->arg ? redirect->arg[0] : NULL;
	if (ptr && ptr[0] == '&')
		ptr++;
	if (ptr[0])
	{
		if (ptr[0] == '-' && (ptr[1] == '\0' || ptr[1] == ' '))
			close(tgt_fd);
		else if (ft_isdigit(ptr[0]) && (ptr[1] == '\0' || ptr[1] == ' '))
		{
			dup2(redirect->fd, tgt_fd);
			close(redirect->fd);
		}
		else if ((redirect->fd = ft_fopen(ptr, "w+")) >= 0)
		{
			dup2(redirect->fd, tgt_fd);
			close(redirect->fd);
		}
		else
			msg_error(ptr);
	}
}

void				d_write_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		if ((redirect->fd = ft_fopen(redirect->arg[0], "a")) >= 0)
		{
			dup2(redirect->fd, tgt_fd);
			close(redirect->fd);
		}
		else
			msg_error(redirect->arg[0]);
	}
}
