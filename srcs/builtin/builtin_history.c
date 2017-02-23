/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:20:14 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/23 22:38:17 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../../incs/shell_21sh.h"

t_options_hist		g_options_hist[] =
{
	{FUNC_NONE, option_none},
	{FUNC_CLEAR, option_clear},
	{FUNC_APPEND, option_append},
	{FUNC_NAPPEND, option_nappend},
	{FUNC_DELETE, option_delete}
};


static int			save_flags(t_hist **hist, char *cmd)
{
	int				i;

	i = 0;
	if (hist == NULL || cmd == NULL || cmd[i] != '-')
		return (ERROR);
	while (cmd[++i] != '\0')
		if (cmd[i] == 'a')
			(*hist)->flags = (*hist)->flags | APPEND;
		else if (cmd[i] == 'c')
			(*hist)->flags = (*hist)->flags | CLEAR;
		else if (cmd[i] == 'd')
			(*hist)->flags = (*hist)->flags | DELETE;
		else if (cmd[i] == 'n')
			(*hist)->flags = (*hist)->flags | NAPPEND;
		else
		{
			ft_putstr_fd("history: ", STDERR_FILENO);
			ft_putchar_fd(cmd[i], STDERR_FILENO);
			ft_putendl_fd(" options : [c] [d offset] [a] [n]", STDERR_FILENO);
			(*hist)->type_error = ERROR_PARAM;
			return (false);
		}
	return (true);
}

static int			get_flags(t_hist *hist,t_cmd *cmd)
{
	int				i;
	int				ret;

	if (hist == NULL || cmd == NULL)
	{
		hist->type_error = ERROR_INCONNU;
		return (ERROR);
	}
	i = 0;
	while (cmd->arg[i] != NULL)
		if (cmd->arg[i++][0] == '-')
			if ((ret = save_flags(&hist, cmd->arg[i - 1])) <= false)
				return (ret);
	return (true);
}

static t_hist		init_hist(t_cmd *cmd)
{
	t_hist			hist;

	ft_bzero(&hist, sizeof(hist));

	if (ft_strcmp(cmd->arg[0], "history") != 0)
	{
		MSG_ERR(hist, WRONG_BUILTIN, hist);
	}
	if (get_flags(&hist, cmd) == ERROR)
		return (hist);
	if (hist.flags & CLEAR)
	{
		if (cmd->arg[1] == NULL || cmd->arg[2] == NULL)
		{
			MSG_ERR(hist, ERROR_OFFSET, hist);
		}
		if ((hist.offset = ft_atoi(cmd->arg[2])) <= 0)
		{
			MSG_ERR(hist, WRONG_OFFSET, hist);
		}
	}
	return (hist);
}

static void			exe_hist(t_hist hist)
{
	if (hist.flags == NONE)
		g_options_hist[FUNC_NONE].f(hist.offset);
	if (hist.flags & CLEAR)
		g_options_hist[FUNC_CLEAR].f(hist.offset);
}

int					builtin_history(t_cmd *cmd)
{
	t_hist			hist;

	if (cmd == NULL)
		return (ERROR);
	hist = init_hist(cmd);
	if (hist.type_error != 0)
		return (false);
	exe_hist(hist);
	return (true);
}
