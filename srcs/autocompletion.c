/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:47:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/30 21:56:59 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static t_entry				*get_last_addr_c(void)
{
	t_line					*curs;
	t_entry					*c;

	if ((curs = g_curs) == NULL)
		return (NULL);
	c = curs->curs;
	while (c != NULL && c->next != NULL)
		c = c->next;
	return (c);
}

static int					move_line_end(void)
{
	int						mem;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	mem = true;
	sh->len_begin = 0;
	while (mem != false)
	{
		if ((mem = move_right()) == ERROR)
			return (ERROR);
		sh->len_begin++;
	}
	return (true);
}

static int					is_autocompletion_bin(t_entry *c)
{
	t_entry					*curs;

	if ((curs = c) == NULL)
		return (ERROR);
	if (curs->c == ' ')
		return (false);
	while (curs != NULL && curs->c != ' ')
	{
		if (curs->c == '/')
			return (false);
		curs = curs->prev;
	}
	return (true);
}

static int					autocompletion_reset_curs(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (sh->len_begin == 0)
		return (false);
	while (--sh->len_begin > 0)
		if (move_left() == ERROR)
			break ;
	return (true);
}

int							put_back_begin_and_reset_curs(char *begin)
{
	t_line					*curs;

	if ((curs = g_curs) == NULL)
		return (ERROR);
	if (begin == NULL)
		return (ERROR);
	if (place_curs() == ERROR || insert_word_in_g_line(begin, &curs) == ERROR ||
			autocompletion_reset_curs() == ERROR)
		return (ERROR);
	return (true);
}

int							del_car_begin_in_g_line(size_t len)
{
	if (g_curs == NULL)
		return (ERROR);
	if (len == 0)
		return (false);
	g_curs->curs = g_curs->line;
	while (g_curs->curs != NULL && g_curs->curs->next != NULL)
		g_curs->curs = g_curs->curs->next;
	while (g_curs->curs != NULL && g_curs->curs->c == ' ')
		del_left();
	del_left();
	len--;
	while (len > 0)
	{
		del_left();
		len--;
	}
	return (true);
}


int							add_word_to_g_line(char **ret, char *begin)
{
	char					*tmp;
	size_t					i;
	size_t					len_ret;
	t_line					*curs;

	if (ret == NULL || begin == NULL || (curs = g_curs) == NULL)
		return (ERROR);
	tmp = *ret;
	if (tmp == NULL || (len_ret = ft_strlen(tmp)) == 0)
		return (false);
	i = 0;
	if (tmp[i] != '\0')
		if (insert_word_in_g_line(&tmp[i], &curs) == ERROR)
			return (ERROR);
	ft_memdel((void**)ret);
	return (true);
}


int							autocompletion(void)
{
	int						ret;
	t_entry					*c;

	if (move_line_end() == ERROR || (c = get_last_addr_c()) == NULL)
		return ((g_curs == NULL) ? ERROR : false);
	if ((ret = is_autocompletion_bin(c)) == ERROR)
		return (ERROR);
	if (ret == true)
		return autocompletion_bin(c);
	return (autocompletion_path(c));
}
