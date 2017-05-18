/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:50:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/18 09:27:55 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

void				change_pipe(int pipefd[2], int s_in, int choice)
{
	if (choice == 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else if (choice == 2)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else if (choice == 3)
	{
		dup2(s_in, STDIN_FILENO);
		close(pipefd[0]);
	}
}

void				save_fd(int std[3])
{
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	std[2] = dup(STDERR_FILENO);
}

void				reset_fd(int std[3])
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	dup2(std[2], STDERR_FILENO);
	close(std[0]);
	close(std[1]);
	close(std[2]);
}

int					redirection_fd_manage(int redirect_fd, int tgt_fd)
{
	dup2(redirect_fd, tgt_fd);
	return (0);
}
