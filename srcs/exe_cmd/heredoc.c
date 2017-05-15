/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:01:48 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/15 17:24:01 by fcapocci         ###   ########.fr       */
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

int						heredoc(char *token)
{
	char				c;
	int					i;
	char				str[PRINT_MAX + 1];
	char				*buff;

	ft_bzero(str, sizeof(str));
	buff = NULL;
	i = 0;
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL )
		return (1);
	g_curs = g_lines;
	g_curs->h_srch = true;
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
					g_curs->count_line++;
					join_tab(&buff, str);
					i = 0;
					ft_bzero(str, sizeof(str));
				}
			}
		}
		if (put_cmd() == ERROR)
			break ;
	}
	if (buff)
	{
		fprintf(debug, "heredoc_line == %s\n", buff);
		ft_memdel((void**)&buff);
	}
	del_g_lines();
	return (0);
}
