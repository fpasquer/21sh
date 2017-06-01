/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 21:13:03 by fcapocci          #+#    #+#             */
/*   Updated: 2017/06/01 01:19:37 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

#define SOUT STDOUT_FILENO

static int				check_and_parse2(char *line, int i)
{
	if (line[i])
	{
		if (line[i] == '<' && line[i + 1] != '<')
			return (2);
		if (line[i + 1] && line[i] == '<' && line[i + 1] == '<')
			return (3);
		if (line[i] == '>' && line[i + 1] != '>')
			return (4);
		if (line[i + 1] && line[i] == '>' && line[i + 1] == '>')
			return (5);
	}
	return (0);
}

static t_cmd			*creat_cmd3(char *line, int size, int i, int index)
{
	t_cmd				*cmd;

	if ((cmd = ft_memalloc(sizeof(t_cmd))) == NULL)
		return (NULL);
	cmd->cmd = check_and_parse2(line, i);
	cmd->line = ft_strsub(line, i - size, tk_fd(line, i) ? size - 1 : size);
	cmd->tgt_fd = cmd->cmd > 3 && !tk_fd(line, i) ? SOUT : tk_fd(line, i);
	cmd->arg = split_quotes(cmd->line);
	if (index == D_GAUCHE && cmd->arg && cmd->arg[0])
		heredoc(NULL, &cmd->arg[0]);
	ft_memdel((void**)&(cmd->line));
	return (cmd);
}

static t_cmd			*creat_cmd2(t_cmd *c2, char *line, int siz, int i)
{
	t_cmd				*cmd;
	t_cmd				*head;

	cmd = NULL;
	head = c2;
	if (!ft_strcmp(line, c2->line))
	{
		c2->cmd = check_and_parse2(line, i);
		ft_memdel((void**)&(c2->line));
		c2->line = ft_strsub(line, i - siz, tk_fd(line, siz) ? siz - 1 : siz);
		if ((c2->arg = split_quotes(c2->line)) == NULL && c2->cmd != 0)
			c2->arg = split_quotes("cat");
		c2->tgt_fd = c2->cmd > 3 && !tk_fd(line, siz) ? SOUT : tk_fd(line, siz);
	}
	else
	{
		while (c2->left)
			c2 = c2->left;
		if ((cmd = creat_cmd3(line, siz, i, c2->cmd)) == NULL)
			return (exit_parse(head, "error to allocate memory"));
		if (cmd->arg && cmd->arg[1])
			tacke_more_arg(head, cmd);
		c2->left = cmd;
	}
	return (head);
}

int						parse_cmd2(t_cmd *cmd, int i)
{
	char				*cpy;
	int					size;

	size = 0;
	while (cmd)
	{
		cpy = ft_strdup(cmd->line);
		i = 0;
		while (i <= (int)ft_strlen(cpy))
		{
			size = 0;
			while (cpy[i] && !check_and_parse2(cpy, i))
				scop(cpy, &i, &size);
			cmd = creat_cmd2(cmd, cpy, size, i);
			i = (check_and_parse2(cpy, i) == 3 ||
				check_and_parse2(cpy, i) == 5 ? i + 2 : i + 1);
		}
		ft_memdel((void**)&cpy);
		cmd = cmd->right;
	}
	return (0);
}

t_cmd					*exit_parse(t_cmd *cmd, char *str)
{
	if (str)
		ft_putendl_fd(str, STDERR_FILENO);
	if (cmd)
		free_cmd(cmd);
	return (NULL);
}
