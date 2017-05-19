/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:01:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/19 23:24:58 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

#define KEY_IGNORE -2
#define PRINT_MAX 1027

static int				init_heredoc_g_lines(void)
{
	del_g_lines();
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL)
		return (1);
	g_curs = g_lines;
	g_curs->h_srch = true;
	g_curs->hdc = true;
	print_prompt();
	return (0);
}

static int			join_tab(char **buff, char *str)
{
	char			*tmp;

	tmp = NULL;
	if (*buff)
		tmp = *buff;
	if ((*buff = ft_strjoin(tmp, str)) == NULL)
		*buff = ft_strdup("");
	if (tmp)
		ft_memdel((void**)&tmp);
	return (0);
}

static int			make_tab_token(char **str, char **buff, char *token)
{
	char			*tmp;

	tmp = *str;
	if ((*str = make_tab()) == NULL)
		*str = ft_strdup("");
	ft_memdel((void**)&tmp);
	if (ft_strequ(*str, token))
		return (1);
	if ((tmp = *str) != NULL || ft_strcmp(tmp, ""))
		*str = ft_strjoin(tmp, "\n");
	if (init_heredoc_g_lines())
		return (1);
	if (join_tab(buff, *str) != 0)
		return (1);
	return (0);
}

static int			heredoc(char *token, char **buff)
{
	char			c;
	char			*str;

	if (init_heredoc_g_lines() != 0)
		return (1);
	str = ft_strdup("");
	while (42)
	{
		c = get_char_keyboard();
		if (place_curs() == ERROR)
			break ;
		if (c != KEY_IGNORE && ft_isascii(c))
			if (add_c_to_line(c, &g_curs) == ERROR)
				break ;
		if (put_cmd() == ERROR)
			break ;
		else if (c != KEY_IGNORE && ft_isascii(c) && c == '\n')
			if (make_tab_token(&str, buff, token) != 0)
				break ;
	}
	if (str)
		ft_memdel((void**)&str);
	del_g_lines();
	return (*buff ? 0 : 1);
}

char				*give_heredoc(t_cmd *redirect, int index)
{
	char			*buff;
	t_cmd			*head;

	head = redirect;
	buff = NULL;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &((get_21sh(NULL))->term_param));
	while (redirect)
	{
		if (index == D_GAUCHE && heredoc(redirect->arg[0], &buff) == 0)
		{
			while (head && head != redirect)
			{
				head->done = 1;
				head = head->left;
			}
			head->done = 1;
		}
		index = redirect->cmd;
		redirect = redirect->left;
	}
	tcsetattr(STDIN_FILENO, TCSADRAIN, &((get_21sh(NULL))->reset));
	return (buff);
}
