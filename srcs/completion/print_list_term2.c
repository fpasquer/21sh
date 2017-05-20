/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_term2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 19:30:00 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:30:01 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int							get_infos_words(t_list_print *list,
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

int							add_list_term(t_list_print **lst, char **word)
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
