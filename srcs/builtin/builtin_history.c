/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:20:14 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/22 19:04:58 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../../incs/shell_21sh.h"

#define CAG cmd->arg

static char			*get_line(t_cmd *cmd, t_hist hist)
{
	char			*ret;
	int				i;
	int				m;
	size_t			len;

	if (cmd == NULL || CAG[0] == NULL || CAG[1] == NULL || hist.type_error != 0)
		return (NULL);
	if (ft_strcmp(CAG[0], "history") != 0 || CAG[1][0] != '-' || CAG[2] == NULL)
		return (NULL);
	i = (hist.flags & CLEAR) ? 3 : 2;
	m = i;
	len = 0;
	while (cmd->arg[i] != NULL)
		len += i == m ? ft_strlen(cmd->arg[i++]) : ft_strlen(cmd->arg[i++]) + 1;
	if ((ret = ft_memalloc((len + i - m + 1) * sizeof(char))) != NULL)
	{
		i = m;
		while (cmd->arg[i] != NULL)
		{
			if (i > m)
				ft_strcat(ret, " ");
			ft_strcat(ret, cmd->arg[i++]);
		}
	}
	return (ret);
}

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
			(*hist)->type_error = ERROR_PARAM;
			return (false);
		}
	return (true);
}

static int			get_flags(t_hist *hist, t_cmd *cmd)
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
		return (msg_err(&hist, WRONG_BUILTIN, &hist));
	}
	if (get_flags(&hist, cmd) != ERROR &&
			(hist.flags & DELETE || hist.flags & APPEND))
	{
		if (cmd->arg[1] == NULL || cmd->arg[2] == NULL)
		{
			return (msg_err(&hist, ERROR_OFFSET, &hist));
		}
		hist.offset = (hist.flags & DELETE) ? ft_atoi(cmd->arg[2]) : 0;
		hist.line = (hist.flags & APPEND) ? get_line(cmd, hist) : NULL;
		if ((hist.flags & DELETE && hist.offset <= 0) ||
				(hist.flags & APPEND && hist.line == NULL))
		{
			return (msg_err(&hist, WRONG_OFFSET, &hist));
		}
	}
	return (hist);
}

int					builtin_history(t_cmd *cmd)
{
	t_hist			hist;

	if (cmd == NULL)
		return (ERROR);
	hist = init_hist(cmd);
	if (hist.type_error != 0)
	{
		if (hist.line != NULL)
			ft_memdel((void**)&hist.line);
		if (hist.type_error == WRONG_BUILTIN ||
				hist.type_error == ERROR_INCONNU)
			ft_putstr_fd("history: erreur", STDERR_FILENO);
		else if (hist.type_error == ERROR_OFFSET ||
				hist.type_error == WRONG_OFFSET)
			ft_putstr_fd("history: erreur de param", STDERR_FILENO);
		ft_putendl_fd(" options : [c] [d offset] [a] [n]", STDERR_FILENO);
		return (false);
	}
	exe_hist(hist);
	if (hist.line != NULL)
		ft_memdel((void**)&hist.line);
	return (true);
}
