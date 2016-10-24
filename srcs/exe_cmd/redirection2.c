/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 13:55:56 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/24 18:12:35 by fcapocci         ###   ########.fr       */
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
			fd = ft_fopen(redirect->arg[0], "w+");
			dup2(fd, 1);
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
			fd = ft_fopen(redirect->arg[0], "a");
			dup2(fd, 1);
	//	}
	}
}
