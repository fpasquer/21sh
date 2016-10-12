/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_term.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 10:34:05 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/12 11:18:31 by fpasquer         ###   ########.fr       */
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

t_list_print				*get_list_term(char **list)
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


char						*print_list_term(t_list_print *list)
{
	size_t					bigger_word;
	unsigned int			len_total;
	unsigned int			nb_word;

	if (get_infos_words(list, &bigger_word, &len_total, &nb_word) == ERROR)
		return (NULL);
	printf("bigger_word = %zu, len_total = %u, nb_word = %u\n", bigger_word, len_total, nb_word);
	return (NULL);
}
