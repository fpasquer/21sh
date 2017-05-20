/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:55:56 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:13:32 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

static int			msg_error(char *str)
{
	ft_putstr_fd("error :", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": permission denied", STDERR_FILENO);
	return (1);
}

int					read_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		if ((redirect->fd = ft_fopen(redirect->arg[0], "r")) >= 0)
			dup2(redirect->fd, tgt_fd);
		else
			return (msg_error(redirect->arg[0]));
	}
	return (0);
}

int					put_heredoc(t_cmd *redirect, int tgt_fd)
{
	int				pipefd[2];

	if (redirect->arg && redirect->arg[0] && tgt_fd == STDIN_FILENO)
	{
		pipe(pipefd);
		ft_putstr_fd(redirect->arg[0], pipefd[1]);
		close(pipefd[1]);
		change_pipe(pipefd, 0, 2);
	}
	else
	{
		ft_putendl_fd("syntax error unexpected token `newline'", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int					write_funct(t_cmd *redirect, int tgt_fd)
{
	char			*ptr;

	if ((ptr = redirect->arg ? redirect->arg[0] : NULL) != NULL)
	{
		if (ptr[0] && ptr[0] == '&')
		{
			ptr++;
			if (ptr[0] && ptr[0] == '-' && (ptr[1] == '\0' || ptr[1] == ' '))
				return (close(tgt_fd));
			else if (ptr[0] && ft_isdigit(ptr[0]) && (!ptr[1] || ptr[1] == ' '))
				return (redirection_fd_manage(ft_atoi(ptr), tgt_fd));
		}
		if ((redirect->fd = ft_fopen(ptr, "w+")) >= 0)
			return (redirection_fd_manage(redirect->fd, tgt_fd));
		else
			return (msg_error(ptr));
	}
	return (0);
}

int					d_write_funct(t_cmd *redirect, int tgt_fd)
{
	if (redirect->arg && redirect->arg[0])
	{
		if ((redirect->fd = ft_fopen(redirect->arg[0], "a")) >= 0)
			return (redirection_fd_manage(redirect->fd, tgt_fd));
		else
			return (msg_error(redirect->arg[0]));
	}
	return (0);
}
