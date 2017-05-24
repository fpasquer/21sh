/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_env3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <fcapocci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 22:56:29 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/24 17:14:26 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"

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
		cmd->env_i = choice;
		cmd->op = content->op;
		cmd->cmd = content->cmd;
		cmd->tgt_fd = content->tgt_fd;
		cmd->right = content->right ? content->right : NULL;
		content->right = cmd;
		cmd->left = content->left;
		content->left = NULL;
		content->op = PV;
		*tab = *tab != NULL ? ft_free_strsplit(*tab) : *tab;
	}
	return (ret);
}
