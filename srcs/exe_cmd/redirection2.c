/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:55:56 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/26 21:15:26 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"
#include "../../incs/shell_21sh.h"

void				pipe_funct(t_cmd *redirect)
{
}

void				read_funct(t_cmd *redirect)
{
}

void				d_read_funct(t_cmd *redirect)
{
}

void				write_funct(t_cmd *redirect)
{
	int				fd;

	if (redirect->arg && redirect->arg[0])
	{
	//	if (check_files(redirect->arg))
	//	{
			if ((fd = ft_fopen(redirect->arg[0], "w+")) >= 0)
				dup2(fd, 1);
			else
			{
				ft_putstr_fd("error :", 2);
				ft_putstr_fd(redirect->arg[0], 2);
				ft_putendl_fd(": permission denied", 2);
			}
	//	}
	}
}

void				d_write_funct(t_cmd *redirect)
{
	int				fd;

	if (redirect->arg && redirect->arg[0])
	{
	//	if (check_files(redirect->arg))
	//	{
			if ((fd = ft_fopen(redirect->arg[0], "a")) >= 0)
				dup2(fd, 1);
			else
			{
				ft_putstr_fd("error :", 2);
				ft_putstr_fd(redirect->arg[0], 2);
				ft_putendl_fd(": permission denied", 2);
			}
	//	}
	}
}
