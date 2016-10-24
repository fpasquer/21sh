/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 04:49:01 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/24 03:05:41 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void				scop(char *line, int *i, int *size)
{
	char			selec;
	int				dup_i;
	int				dup_size;

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

	i = len_y(cmd->arg);
	index = len_y(red->arg);
	if ((new_arg = ft_memalloc(sizeof(char*) * (i + index))) == NULL)
		ft_putendl_fd("error to allocate memory for **new_arg", 2);
	i = 0;
	index = 1;
	while (cmd->arg[i])
	{
		new_arg[i] = ft_strdup(cmd->arg[i]);
		i++;
	}
	while (red->arg[index])
	{
		new_arg[i] = ft_strdup(red->arg[index]);
		ft_memdel((void**)&(red->arg[index]));
		index++;
		i++;
	}
	new_arg[i] = NULL;
	ft_free_strsplit(cmd->arg);
	cmd->arg = new_arg;
}
