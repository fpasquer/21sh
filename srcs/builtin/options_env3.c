/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 22:56:29 by fcapocci          #+#    #+#             */
/*   Updated: 2017/06/01 05:30:31 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#define FLAG_I 1
#define FLAG_U 8

#define OPT_WRONG -2
#define PARAM -3

static t_env		*save_env_modif(char **environ)
{
	t_env			*lst_env;
	int				i;

	i = 0;
	lst_env = NULL;
	if (environ == NULL)
		return (NULL);
	while (environ[i] != NULL)
	{
		if (add_env(&lst_env, environ[i], i, true) == ERROR)
			break ;
		i++;
	}
	return (lst_env);
}

static void			filler_cmd_created(t_cmd *cmd, t_cmd *content)
{
	cmd->op = content->op;
	cmd->cmd = content->cmd;
	cmd->tgt_fd = content->tgt_fd;
	cmd->right = content->right ? content->right : NULL;
	content->right = cmd;
	cmd->left = content->left;
	content->left = NULL;
	content->op = PV;
	content->done = 0;
}

int					take_cmd_if_exist(char **tmp_line, char ***tab,
			t_cmd *content, int choice)
{
	int				ret;
	t_cmd			*cmd;

	ret = 0;
	if (choice == 1)
		ret = tab_env_i(tmp_line, tab);
	else if (choice == 2)
		ret = tab_env_u(tmp_line, tab, content);
	else if (choice == 3)
		ret = tab_env(tmp_line, tab, content);
	if ((cmd = parse_cmd(*tmp_line, NULL, 0)) != NULL && cmd->line != NULL)
	{
		cmd->env = save_env_modif(*tab);
		cmd->env_i = cmd->env == NULL ? 1 : 0;
		filler_cmd_created(cmd, content);
		*tab = *tab != NULL ? ft_free_strsplit(*tab) : *tab;
		ret = ENV_CREAT;
	}
	return (ret);
}

int					check_if_env_creat_cmd(t_cmd *content)
{
	char			flags;
	char			**tab;
	int				ret;
	char			*tmp_line;

	tmp_line = content->line;
	tab = NULL;
	if ((flags = get_flags_env(&tmp_line, content->env)) == PARAM
			|| flags == OPT_WRONG)
		return (ERROR);
	if (flags == ERROR)
		return (ERROR);
	if ((flags & FLAG_I) != 0)
		ret = take_cmd_if_exist(&tmp_line, &tab, content, 1);
	else if ((flags & FLAG_U) != 0)
		ret = take_cmd_if_exist(&tmp_line, &tab, content, 2);
	else
		ret = take_cmd_if_exist(&tmp_line, &tab, content, 3);
	if (tab != NULL)
		ft_free_strsplit(tab);
	return (ret);
}
