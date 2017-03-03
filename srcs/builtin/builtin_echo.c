/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:06:16 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/03 21:36:10 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

#define FLAG_NONE 0
#define FLAG_WRONG 8
#define FLAG_N 2

static char			take_flags(char *str)
{
	int				i;

	i = 0;
	if (!str)
		return (FLAG_NONE);
	while (ft_isspace(str[i]))
		i++;
	if (str[i++] == '-')
		if (str[i] == 'n' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			return (FLAG_N);
	return (FLAG_NONE);
}

static void			print_echo(char *str)
{
	int				i;

	i = 0;
	if (str && str[i] != '\0')
	{
		while (str[i] && str[i] != '\0')
		{
			if (str[i] != '\"' && str[i] != '\\' && str[i] != '\'')
				ft_putchar_fd(str[i], STDOUT_FILENO);
			i++;
		}
	}
}

int					builtin_echo(t_cmd *cmd)
{
	int				i;
	unsigned char	flags;
	unsigned char	ret;

	i = 1;
	flags = FLAG_NONE;
	ret = FLAG_NONE;
	if (!cmd->arg)
		return (false);
	while (cmd->arg[i])
	{
		while((ret = take_flags(cmd->arg[i])) > 0)
		{
			flags = ret;
			i++;
		}
		if (cmd->arg[i])
			print_echo(cmd->arg[i++]);
	}
	if (flags == FLAG_NONE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (true);
}
