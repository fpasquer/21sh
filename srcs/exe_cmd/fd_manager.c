/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:50:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/20 06:37:56 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

void				change_pipe(int pipefd[2], int s_in, int choice)
{
	if (choice == 1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
	}
	else if (choice == 2)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
	}
	else if (choice == 3)
	{
		dup2(s_in, STDIN_FILENO);
		close(pipefd[0]);
	}
}

void				save_fd(int *s_in, int *s_out)
{
	*s_in = dup(STDIN_FILENO);
	*s_out = dup(STDOUT_FILENO);
}

void				reset_fd(int s_in, int s_out)
{
	dup2(s_in, STDIN_FILENO);
	dup2(s_out, STDOUT_FILENO);
	close(s_in);
	close(s_out);
}
