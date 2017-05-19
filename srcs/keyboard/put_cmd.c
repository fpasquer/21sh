/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 19:28:52 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/19 21:25:51 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#include <limits.h>

#define PRINT_MAX 500

static int					replace_i(void)
{
	size_t					i;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	i = curs->i;
	while (i++ + 1 < curs->len)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	return (true);
}

static t_entry				*put_cmd_char_in_tab(char buff[], t_entry *c,
		size_t i)
{
	size_t					end;
	size_t					l_select_color;
	size_t					l_reset_color;
	bool					select;

	l_select_color = ft_strlen(SELECTED_COLOR);
	l_reset_color = ft_strlen(RESET_COLOR);
	end = PRINT_MAX - l_select_color - l_reset_color;
	select = false;
	i = 0;
	while (i < end && c != NULL)
	{
		if (c->select == true && select == false)
			ft_strcat(buff, SELECTED_COLOR);
		else if (c->select == false && select == true)
			ft_strcat(buff, RESET_COLOR);
		if (c->select != select)
			i = c->select == true ? l_select_color + i : l_reset_color + i;
		select = c->select;
		buff[i++] = c->c;
		c = c->next;
	}
	if (select == true)
		ft_strcat(buff, RESET_COLOR);
	return (c);
}

int							put_cmd(void)
{
	char					buff[PRINT_MAX + 1];
	size_t					i;
	t_line					*curs;
	t_entry					*c_line;

	if (clean_and_put_prompt() != true || (curs = g_lines) == NULL)
		return (ERROR);
	i = 0;
	while (curs != NULL)
	{
		c_line = curs->line;
		while (c_line != NULL)
		{
			ft_bzero(buff, sizeof(buff));
			c_line = put_cmd_char_in_tab(buff, c_line, i);
			ft_putstr_fd(buff, STDOUT_FILENO);
		}
		if ((curs = curs->next) != NULL)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (replace_i());
}
