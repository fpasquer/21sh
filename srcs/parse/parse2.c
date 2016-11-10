/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 21:13:03 by fcapocci          #+#    #+#             */
/*   Updated: 2016/11/10 22:17:22 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

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

static void				creat_cmd3(t_cmd *cmd, char *line, int size, int i)
{
	cmd->right = NULL;
	cmd->left = NULL;
	cmd->cmd = check_and_parse2(line, i);
	cmd->op = 0;
	cmd->done = 0;
	cmd->tgt_fd = STDOUT_FILENO;
	cmd->line = ft_strsub(line, i - size, size);
	cmd->arg = split_quotes(cmd->line);
	ft_memdel((void**)&(cmd->line));
}

static t_cmd			*creat_cmd2(t_cmd *cmd2, char *line, int size, int i)
{
	t_cmd				*cmd;
	t_cmd				*head;

	head = cmd2;
	if (!ft_strcmp(line, cmd2->line))
	{
		ft_memdel((void**)&(cmd2->line));
		cmd2->line = ft_strsub(line, i - size, size);
		cmd2->cmd = check_and_parse2(line, i);
		cmd2->arg = split_quotes(cmd2->line);
		cmd2->done = 0;
		cmd2->tgt_fd = STDOUT_FILENO;
	}
	else
	{
		if ((cmd = ft_memalloc(sizeof(t_cmd))) == NULL)
			return (exit_parse(head, "error to allocate memory"));
		while (cmd2->left)
			cmd2 = cmd2->left;
		cmd2->left = cmd;
		creat_cmd3(cmd, line, size, i);
		if (cmd->arg && cmd->arg[1])
			tacke_more_arg(head, cmd);
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

t_cmd				*exit_parse(t_cmd *cmd, char *str)
{
	if (str)
		ft_putendl_fd(str, STDERR_FILENO);
	if (cmd)
		free_cmd(cmd);
	return (NULL);
}
