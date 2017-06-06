/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 04:49:01 by fcapocci          #+#    #+#             */
/*   Updated: 2017/06/07 01:36:09 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void				scop(char *line, int *i, int *size)
{
	char			selec;
	size_t			dup_i;
	size_t			dup_size;

	dup_i = (*i) + 1;
	dup_size = (*size) + 1;
	selec = line[*i];
	if (line[*i] == '\"' || line[*i] == '\'')
	{
		while (line[dup_i] && line[dup_i] != selec)
		{
			dup_size++;
			dup_i++;
		}
		if (dup_i < ft_strlen(line))
		{
			*size = dup_size;
			*i = dup_i;
		}
	}
	(*size)++;
	(*i)++;
}

void				tacke_more_arg(t_cmd *cmd, t_cmd *red)
{
	int				i;
	int				index;
	char			**new_arg;

	i = cmd->arg ? len_y(cmd->arg) : 0;
	index = len_y(red->arg);
	if ((new_arg = ft_memalloc(sizeof(char*) * (i + index))) == NULL)
		ft_putendl_fd("error to allocate memory for **new_arg", STDERR_FILENO);
	i = 0;
	index = 1;
	while (cmd->arg && cmd->arg[i])
	{
		new_arg[i] = ft_strdup(cmd->arg[i]);
		i++;
	}
	while (red->arg && red->arg[index])
	{
		new_arg[i] = ft_strdup(red->arg[index]);
		ft_memdel((void**)&(red->arg[index]));
		index++;
		i++;
	}
	if (((new_arg[i] = NULL) == NULL) && cmd->arg)
		ft_free_strsplit(cmd->arg);
	cmd->arg = new_arg;
}

int					tk_fd(char *line, int siz)
{
	int				ret;

	ret = 0;
	if (line && siz > 0 && line[siz] && line[siz] == '>')
	{
		ft_putnbr_fd(siz, 2);
		ft_putendl_fd(" --> size", 2);
		if (siz < 2 && line[siz - 1] && ft_isdigit(line[siz - 1]))
			ret = ft_atoi(&(line[siz - 1]));
		else if (line[siz - 1] && ft_isdigit(line[siz - 1]) && line[siz - 2]
				&& line[siz - 2] == ' ')
			ret = ft_atoi(&(line[siz - 1]));
	}
	ft_putnbr_fd(ret, 2);
	ft_putendl_fd(" --> ret", 2);
	return (ret);
}
