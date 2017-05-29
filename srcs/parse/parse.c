/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 14:49:47 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/30 01:11:33 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static int				check_and_parse(char *line, int i)
{
	if (line[i])
	{
		if (line[i] == ';')
			return (1);
		if (line[i + 1] && line[i] == '&' && line[i + 1] == '&')
			return (2);
		if ((line[i + 1] && line[i] == '|' && line[i + 1] != '|')
				|| (line[i] == '|' && line[i + 1] == 0))
			return (3);
		if (line[i + 1] && line[i] == '|' && line[i + 1] == '|')
			return (4);
	}
	return (0);
}

static t_cmd			*create_cmd(t_cmd *cmd2, char *line, int size, int i)
{
	t_cmd				*cmd;
	t_cmd				*head;

	head = cmd2;
	if ((cmd = ft_memalloc(sizeof(t_cmd))) == NULL)
		return (NULL);
	cmd->right = NULL;
	cmd->left = NULL;
	cmd->arg = NULL;
	cmd->op = check_and_parse(line, i);
	cmd->done = -1;
	cmd->line = ft_strsub(line, i - size, size);
	if (cmd2)
	{
		while (cmd2->right)
			cmd2 = cmd2->right;
		cmd2->right = cmd;
		return (head);
	}
	return (cmd);
}

static int				check_error_parse(t_cmd *cmd)
{
	if ((cmd->op != 0 && !cmd->arg) ||
			(cmd->op != 0 && cmd->arg && !cmd->arg[0]) ||
			(cmd->op == 3 && (!cmd->right || (cmd->right && !cmd->right->arg))))
		return (-1);
	while (cmd)
	{
		if ((cmd->arg == NULL && cmd->right) ||
				(cmd->arg && cmd->arg[0] == NULL && cmd->right))
			return (-1);
		if ((cmd->arg == NULL && cmd->op != 0) ||
				(cmd->arg && cmd->arg[0] == NULL && cmd->op != 0))
			return (-1);
		if ((cmd->left && cmd->left->arg && cmd->left->arg[0] == NULL) ||
				(cmd->left && cmd->left->arg == NULL))
			return (-1);
		if ((cmd->op > 1 && cmd->right && cmd->right->arg &&
				!cmd->right->arg[0]) || (cmd->op > 1 && !cmd->right))
			return (-1);
		cmd = cmd->right;
	}
	return (0);
}

t_cmd					*parse_cmd(char *line, t_cmd *cmd, int i)
{
	int					size;

	if (i != 0 || cmd != NULL || line == NULL || line[0] == '\0')
		return (NULL);
	while (i < (int)ft_strlen(line))
	{
		size = 0;
		while (line[i] && !check_and_parse(line, i))
			scop(line, &i, &size);
		if ((cmd = create_cmd(cmd, line, size, i)) == NULL)
			return (exit_parse(cmd, "error to allocate memory"));
		i = (check_and_parse(line, i) == 3 || check_and_parse(line, i) == 4)
			? i + check_and_parse(line, i) - 2 : i + check_and_parse(line, i);
	}
	if (parse_cmd2(cmd, 0) < 0)
		return (exit_parse(cmd, "error parse cmd"));
	return (!check_error_parse(cmd) ? cmd : exit_parse(cmd, "parse error"));
}

void					free_cmd(t_cmd *cmd)
{
	int					i;

	i = 0;
	if (cmd)
	{
		free_cmd(cmd->left);
		free_cmd(cmd->right);
		if (cmd->line)
			ft_memdel((void**)&(cmd->line));
		if (cmd->arg)
		{
			while (cmd->arg[i])
			{
				ft_memdel((void**)&(cmd->arg[i]));
				i++;
			}
			ft_memdel((void**)&(cmd->arg[i]));
			ft_memdel((void**)&(cmd->arg));
		}
		if (cmd->env)
			del_list_env(&(cmd->env));
		ft_memdel((void**)&cmd);
	}
}
