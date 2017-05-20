/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_term.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:43:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:30:21 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static t_list_print			*get_list_term(char **list)
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
	if (bigger_word + 1 < sh->win.ws_col)
	{
		len = sh->win.ws_col / (bigger_word + 1);
		len = sh->win.ws_col / len;
		nb_word_line = sh->win.ws_col / len;
	}
	else
	{
		ft_putendl("Windows to small");
		return (NULL);
	}
	if (select == true)
		return (put_words_event(lst, len, nb_word_line));
	else
		return (put_words2(lst, len, nb_word_line));
}

char						*print_list_term(t_21sh *sh, char **list,
		bool select)
{
	char					*adr;
	t_list_print			*lst;

	if (sh == NULL)
		return (NULL);
	if (len_y(list) == 1 && select == true)
	{
		place_curs();
		return (ft_strdup(list[0]));
	}
	if ((lst = get_list_term(list)) == NULL)
		return (NULL);
	adr = NULL;
	adr = put_words1(sh, lst, select);
	del_list_term(&lst);
	return (adr);
}
