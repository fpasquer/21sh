/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_history2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:45:00 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/22 18:41:42 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"

t_options_hist		g_options_hist[] =
{
	{FUNC_NONE, option_none},
	{FUNC_CLEAR, option_clear},
	{FUNC_APPEND, option_append},
	{FUNC_NAPPEND, option_nappend},
	{FUNC_DELETE, option_delete}
};

t_hist					msg_err(t_hist *hist, int val, t_hist *ret)
{
	hist->type_error = val;
	return (*ret);
}

int						option_nappend(t_hist hist)
{
	hist.offset = (int)hist.offset;
	return (true);
}

int						exe_hist(t_hist hist)
{
	int				ret;

	ret = true;
	if (ret == true && hist.flags == NONE)
		ret = g_options_hist[FUNC_NONE].f(hist);
	else
	{
		if (ret == true && hist.flags & CLEAR)
			ret = g_options_hist[FUNC_CLEAR].f(hist);
		else if (ret == true && hist.flags & DELETE)
			ret = g_options_hist[FUNC_DELETE].f(hist);
		if (ret == true && hist.flags & APPEND)
			ret = g_options_hist[FUNC_APPEND].f(hist);
	}
	return (ret);
}
