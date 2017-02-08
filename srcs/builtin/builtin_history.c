/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:20:14 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/08 16:44:10 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../../incs/shell_21sh.h"

int					builtin_history(t_cmd *cmd)
{
	if (!cmd)
		return (ERROR);
	if (print_history() != true)
		return (ERROR);
	return (true);
}
