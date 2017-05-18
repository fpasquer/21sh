/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:01:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/18 09:11:56 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

#define KEY_IGNORE -2
#define PRINT_MAX 500

static int				join_tab(char **buff, char *str)
{
	size_t				size;
	char				*tmp;

	tmp = NULL;
	if ((size = ft_strlen(str)) == 0 || buff == NULL)
		return (-1);
	if (*buff)
		tmp = *buff;
	*buff = ft_strjoin(tmp, str);
	if (tmp)
		ft_memdel((void**)&tmp);
	return (0);
}

static int				heredoc(char *token, char **buff)
{
	char				c;
	int					i;
	char				str[PRINT_MAX + 1];

	ft_bzero(str, sizeof(str));
	i = 0;
	fprintf(debug, "pass  ICI\n");
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL )
		return (1);
	g_curs = g_lines;
	g_curs->hdc = true;
	print_prompt();
	while (42)
	{
		c = get_char_keyboard();
		if (place_curs() == ERROR)
			break ;
		if (c != KEY_IGNORE && ft_isascii(c))
		{
			if (add_c_to_line(c, &g_curs) == ERROR)
				break ;
			if (c == '\n' && ft_strequ(str, token))
				break ;
			else
			{
				str[i++] = c;
				if (c == '\n')
				{
					join_tab(buff, str);
					i = 0;
					ft_bzero(str, sizeof(str));
				}
			}
		}
		if (put_cmd() == ERROR)
			break ;
	}
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
	fprintf(debug, "pass la buff == %s\n", buff);
	return (buff);
}
