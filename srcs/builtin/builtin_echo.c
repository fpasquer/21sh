/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:06:16 by fcapocci          #+#    #+#             */
/*   Updated: 2017/06/03 19:59:33 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

#define FLAG_NONE 0
#define FLAG_N 2

static int				take_flags(char *str, unsigned char *flags)
{
	int					i;

	i = 0;
	if (!str)
		return (-1);
	if (str[i] == '-')
	{
		while (str[++i] != '\0')
		{
			if (str[i] == 'n')
				*flags = *flags | FLAG_N;
			else
			{
				*flags = FLAG_NONE;
				return (-1);
			}
		}
		return (1);
	}
	return (0);
}

static void				print_echo(char *str)
{
	int					i;

	i = 0;
	if (str && str[i] != '\0')
	{
		while (str[i] && str[i] != '\0')
		{
			if (str[i] != '\\')
				ft_putchar_fd(str[i], STDOUT_FILENO);
			i++;
		}
	}
}

int						builtin_echo(t_cmd *cmd)
{
	int					i;
	int					save;
	unsigned char		flags;

	i = 1;
	flags = FLAG_NONE;
	if (!cmd->arg)
		return (false);
	while (take_flags(cmd->arg[i], &flags) == 1)
		i++;
	save = i;
	while (cmd->arg[i])
	{
		if (i != save)
			ft_putchar_fd(' ', STDOUT_FILENO);
		print_echo(cmd->arg[i++]);
	}
	if ((flags & FLAG_N) == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (true);
}
