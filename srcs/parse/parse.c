/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 14:49:47 by fcapocci          #+#    #+#             */
/*   Updated: 2016/10/12 17:37:40 by fcapocci         ###   ########.fr       */
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

t_cmd					*parse_cmd(char *line)
{
	int					i;
	int					size;
	t_cmd				*cmd;

	cmd = NULL;
	i = ft_strlen(line) - 1;
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
		return (NULL);
	//print_cmd(cmd);
	return (cmd);
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
		ft_putstr("father link num = ");
		ft_putnbr(cmpt);
		ft_putchar('\n');
		ft_putstr("link op = ");
		ft_putnbr(cmd->op);
		ft_putchar('\n');
		ft_putstr("link cmd = ");
		ft_putnbr(cmd->cmd);
		ft_putstr("\nline = ");
		if (cmd->line)
			ft_putendl(cmd->line);
		else
			ft_putchar('\n');
		ft_putstr("agr :\n");
		i = 0;
		if (cmd->arg)
		{
			while (cmd->arg[i])
			{
				ft_putendl(cmd->arg[i]);
				i++;
			}
		}
		else
			ft_putchar('\n');
		ft_putchar('\n');
		curs = cmd->left;
		cmpt2 = 1;
		while (curs)
		{
			ft_putstr("child link num = ");
			ft_putnbr(cmpt);
			ft_putchar('.');
			ft_putnbr(cmpt2);
			ft_putchar('\n');
			ft_putstr("link cmd = ");
			ft_putnbr(curs->cmd);
			ft_putstr("\nline = ");
			if (curs->line)
				ft_putendl(curs->line);
			else
				ft_putchar('\n');
			ft_putstr("agr :\n");
			i = 0;
			if (curs->arg)
			{
				while (curs->arg[i])
				{
					ft_putendl(curs->arg[i]);
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
