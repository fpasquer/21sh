/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 22:31:09 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/17 23:26:54 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"

int					search_history(void)
{
	char			*srch_line;

	g_curs->h_srch = true;
	if ((srch_line = get_line_entree()) == NULL)
		return (g_curs->h_srch = false);
	g_curs->h_srch = false;
	return (true);
}
