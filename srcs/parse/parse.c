/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 14:49:47 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/13 21:37:40 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static int				check_and_parse(char *line, int i)
{
	if (i < 0)
		return (0);
	if (line[i] == ';')
		return (1);
	if (i - 1 >= 0 && line[i] == '&' && line[i - 1] == '&')
		return (2);
	if (i - 1 >= 0 && line[i] == '|' && line[i - 1] == '|')
		return (3);
	return (0);
}

static t_cmd			*create_cmd(t_cmd *cmd2, char *line, int size, int i)
{
	t_cmd				*cmd;

	if ((cmd = ft_memalloc(sizeof(t_cmd))) == NULL)
		return (NULL);
	cmd->right = NULL;
	cmd->left = NULL;
	cmd->arg = NULL;
	cmd->op = check_and_parse(line, i);
	cmd->done = 0;
	cmd->line = ft_strsub(line, i + 1, size);
	if (cmd2)
		cmd->right = cmd2;
	return (cmd);
}

static int				check_error_parse(t_cmd *cmd)
{
	if (cmd->op != 0 || (cmd->arg[0] == NULL && cmd->right))
		return (-1);
	cmd = cmd->right;
	while (cmd)
	{
		if ((cmd->arg == NULL && cmd->right) ||
				(cmd->arg && cmd->arg[0] == NULL && cmd->right))
			return (-1);
		if ((cmd->arg == NULL && cmd->op == 2) ||
				(cmd->arg && cmd->arg[0] == NULL && cmd->op == 2))
			return (-1);
		if ((cmd->arg == NULL && cmd->op == 3) ||
				(cmd->arg && cmd->arg[0] == NULL && cmd->op == 3))
			return (-1);
		cmd = cmd->right;
	}
	return (0);
}

t_cmd					*parse_cmd(char *line)
{
	int					i;
	int					size;
	t_cmd				*cmd;

	cmd = NULL;
	if (line == NULL)
		return (NULL);
	if ((i = ft_strlen(line) - 1) < 0)
		return (NULL);
	while (i >= 0)
	{
		size = 0;
		while (i >= 0 && !check_and_parse(line, i))
		{
			size++;
			i--;
		}
		if ((cmd = create_cmd(cmd, line, size, i)) == NULL)
			return (NULL);
		i = (check_and_parse(line, i)) == 3 ? i - 2 :
			i - check_and_parse(line, i);
	}
	if (parse_cmd2(cmd, cmd, 0) < 0)
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
		ft_memdel((void**)&cmd);
	}
}

void					print_cmd(t_cmd *cmd)
{
	int					cmpt;
	int					cmpt2;
	int					i;
	t_cmd				*curs;

	cmpt = 0;
	while (cmd)
	{
		printf("father link num = %d\n", cmpt);
		printf("link op = %d\n", cmd->op);
		printf("link cmd = %d\n", cmd->cmd);
		printf("line = %s\n", cmd->line);
		printf("argc = %d\n", cmd->argc);
		i = 0;
		if (cmd->arg)
		{
			while (cmd->arg[i])
			{
				printf("cmd->arg[%d] = %s\n", i, cmd->arg[i]);
				i++;
			}
		}
		ft_putchar('\n');
		curs = cmd->left;
		cmpt2 = 1;
		while (curs)
		{
			printf("child link num = %d.%d\n", cmpt, cmpt2);
			printf("link op = %d\n", curs->op);
			printf("link cmd = %d\n", curs->cmd);
			printf("line = %s\n", curs->line);
			printf("argc = %d\n", curs->argc);
			i = 0;
			if (curs->arg)
			{
				while (curs->arg[i])
				{
					printf("cmd->arg[%d] = %s\n", i, curs->arg[i]);
					i++;
				}
			}
			ft_putchar('\n');
			cmpt2++;
			curs = curs->left;
		}
		cmpt++;
		cmd = cmd->right;
	}
}
