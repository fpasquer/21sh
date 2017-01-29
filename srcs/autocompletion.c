/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 21:47:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/29 21:03:47 by fpasquer         ###   ########.fr       */
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
	while (c != NULL && c->c == ' ')
		c = c->prev;
	return (c);
}

static int					move_line_end(void)
{
	int						mem;

	mem = true;
	while (mem != false)
	{
		if ((mem = move_right()) == ERROR)
			return (ERROR);
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
																				{
																					fprintf(debug, "ici line %d\n", __LINE__);
		return ((g_curs == NULL) ? ERROR : false);
																				}
	if ((ret = is_autocompletion_bin(c)) == ERROR)
		return (ERROR);
																				fprintf(debug, "ret = %d\n", ret);
	if (ret == true)
		return autocompletion_bin(c);
	return (autocompletion_path(c));
}
