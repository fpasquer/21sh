/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:20:14 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/22 22:48:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../../incs/shell_21sh.h"

# define MSG_ERR(hist, val, ret) hist.type_error = val;return (ret)

# define NONE 0
# define CLEAR 1
# define APPEND 2
# define NAPPEND 4
# define DELETE 8

# define WRONG_BUILTIN 1
# define ERROR_INCONNU 2
# define ERROR_PARAM 3

typedef struct		s_options_hist
{
	int				i;
	int				(*f)(int);
}					t_options_hist;

int					option_none(int offset);
int					option_clear(int offset);
int					option_append(int offset);
int					option_nappend(int offset);
int					option_delete(int offset);

t_options_hist		g_options_hist[] =
{
	{NONE, option_none},
	{CLEAR, option_clear},
	{APPEND, option_append},
	{NAPPEND, option_nappend},
	{DELETE, option_delete}
};

typedef struct		s_hist
{
	int				flags;
	int				offset;
	int				i;
	int				type_error;
}					t_hist;

int					option_none(int offset)
{
	unsigned int	i;
	t_21sh			*sh;
	t_history		*tmp;

	offset = (int)offset;
	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((tmp = sh->hist) != NULL)
	{
		i = 1;
		while (tmp != NULL)
		{
			ft_putnbr_fd(i, STDOUT_FILENO);
			ft_putstr_fd(": ", STDOUT_FILENO);
			ft_putendl_fd(tmp->line, STDOUT_FILENO);
			tmp = tmp->next;
			i++;
		}
	}
	return (i == 0 ? false : true);
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
	return (hist);
}

static void			exe_hist(t_hist hist)
{
	if (hist.flags == NONE)
		g_options_hist[NONE].f(0);
	if (hist.flags & CLEAR)
		g_options_hist[CLEAR].f(0);
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
