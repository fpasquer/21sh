/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:58:42 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 10:30:59 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_21SH

#define SHELL_21SH

#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include "../libft/libft.h"

#define ERROR -1

/*
**	**path :		path tableau a 2 dimensions des paths
**	*path_line:		variable env recu dans le main
*/

typedef struct				s_21sh
{
	char					**path;
	char					*path_line;
}							t_21sh;

/*
**	init_21sh.h
*/
t_21sh						*init_21sh(char **env);
t_21sh						*get_21sh(t_21sh *shell_21sh);
int							del_21sh();


#endif
