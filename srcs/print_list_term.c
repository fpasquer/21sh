/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_term.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 10:34:05 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/12 17:42:20 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"

static int					get_infos_words(t_list_print *list,
		size_t *bigger_word, unsigned int *len_total, unsigned int *nb_word)
{
	t_list_print			*curs;

	*bigger_word = 0;
	*len_total = 0;
	*nb_word = 0;
	if ((curs = list) == NULL)
		return (ERROR);
	while (curs != NULL)
	{
		*bigger_word = (*bigger_word < curs->len) ? curs->len : *bigger_word;
		*len_total += curs->len;
		*nb_word = *nb_word + 1;
		curs = curs->next;
	}
	return (true);
}

static int					add_list_term(t_list_print **lst, char **word)
{
	t_list_print			*new;
	t_list_print			*curs;

	if (lst == NULL || word == NULL || *word == NULL ||
			(new = ft_memalloc(sizeof(*new))) == NULL)
		return (ERROR);
	new->word = *word;
	new->len = ft_strlen(*word);
	if ((curs = *lst) != NULL)
	{
		new->next = *lst;
		(*lst)->prev = new;
	}
	(*lst) = new;
	return (true);
}

static t_list_print				*get_list_term(char **list)
{
	unsigned int			i;
	t_list_print			*lst;

	if (list == NULL)
		return (NULL);
	lst = NULL;
	i = 0;
	while (list[i] != NULL)
		if (add_list_term(&lst, &list[i++]) == ERROR)
			return (NULL);
	return (lst);
}

static int					del_list_term(t_list_print **lst)
{
	t_list_print			*tmp;
	t_list_print			*curs;

	if (lst == NULL)
		return (ERROR);
	curs = *lst;
	while (curs != NULL)
	{
		tmp = curs->next;
		ft_memdel((void**)&curs);
		curs = tmp;
	}
	return (true);
}

static char					*put_words2(t_list_print *lst, int len,
		int nb_word_line)
{
	int						x;
	int						y;
	int						i;
	t_list_print			*curs;

	if (lst == NULL || len <= 0 || nb_word_line <= 0)
		return (NULL);
	curs = lst;
	y = 0;
	while (curs != NULL)
	{
		x = 0;
		while (curs != NULL && x++ < nb_word_line)
		{
			i = ft_strlen(curs->word);
			ft_putstr(curs->word);
			while (i++ < len)
				ft_putchar(' ');
			curs = curs->next;
		}
		ft_putchar('\n');
		y++;
	}
	return (lst->word);
}

static char					*put_words1(t_21sh *sh, t_list_print *lst,
		bool select)
{
	size_t					bigger_word;
	unsigned int			len_total;
	unsigned int			nb_word;
	int						len;
	int						nb_word_line;

	if (sh == NULL || lst == NULL)
		return (NULL);
	if (get_infos_words(lst, &bigger_word, &len_total, &nb_word) == ERROR)
		return (NULL);
	len = sh->win.ws_col / (bigger_word + 1);
	len = sh->win.ws_col / len;
	nb_word_line = sh->win.ws_col / len;
	if (select == true)
		return (put_words_event(lst, len, nb_word_line, sh));
	else
		return (put_words2(lst, len, nb_word_line));
}


char						*print_list_term(t_21sh *sh, char **list,
		bool select)
{
	char					*adr;
	t_list_print			*lst;

	if ((lst = get_list_term(list)) == NULL)
		return (NULL);
	if (sh == NULL)
		return (NULL);
	adr = NULL;
	adr = put_words1(sh, lst, select);
	del_list_term(&lst);
	return (adr);
}
