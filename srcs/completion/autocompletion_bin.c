/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_bin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 21:31:08 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:25:54 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static unsigned int			get_nb_match_word(t_bin *list, char *word)
{
	unsigned int			nb_match_word;
	size_t					len_word;
	t_bin					*curs;

	if ((curs = list) == NULL || word == NULL)
		return (0);
	nb_match_word = 0;
	if ((len_word = ft_strlen(word)) == 0)
		return (0);
	while (curs != NULL)
	{
		if (ft_strncmp(curs->name, word, len_word) == 0)
			nb_match_word++;
		curs = curs->n_dico;
	}
	return (nb_match_word);
}

static char					**make_list_match(unsigned int y,
		char *begin, t_bin *dico)
{
	char					**list_match;
	size_t					len_word;
	unsigned int			i;
	t_bin					*curs;

	if (y == 0 || begin == NULL || (curs = dico) == NULL)
		return (NULL);
	if ((len_word = ft_strlen(begin)) == 0)
		return (0);
	if ((list_match = ft_memalloc(sizeof(*list_match) * (y + 1))) == NULL)
		return (NULL);
	i = 0;
	while (curs != NULL)
	{
		if (ft_strncmp(curs->name, begin, len_word) == 0)
			if ((list_match[i++] = ft_strdup(curs->name)) == NULL)
				return (list_match);
		curs = curs->n_dico;
	}
	return (list_match);
}

static int					put_autocompletion_bin(char *begin, int i)
{
	char					**list_match;
	char					*ret;
	unsigned int			nb_match_word;
	t_bin					*dico;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (i < 0 || i >= SIZE_DICO || begin == NULL || begin[0] == '\0' ||
			(dico = sh->dico[i]) == NULL)
		return (ERROR);
	nb_match_word = get_nb_match_word(dico, begin);
	if ((list_match = make_list_match(nb_match_word, begin, dico)) == NULL)
		return (nb_match_word == 0 ? false : ERROR);
	ret = print_list_term(sh, list_match, true);
	ft_free_strsplit(list_match);
	return (add_word_to_g_line(&ret, begin));
}

int							autocompletion_bin(t_entry *c)
{
	char					*beg;
	int						i;
	int						ret;
	t_line					*curs;

	if ((curs = g_curs) == NULL)
		return (ERROR);
	if ((beg = get_begin_bin(c)) == NULL)
		return (false);
	if ((beg[0] >= 'a' && beg[0] <= 'z') || (beg[0] >= 'A' && beg[0] <= 'Z'))
		i = (beg[0] >= 'a' && beg[0] <= 'z') ? beg[0] - 'a' : beg[0] - 'A';
	else
		i = SIZE_DICO - 1;
	if ((ret = put_autocompletion_bin(beg, i)) == false)
	{
		place_curs();
		insert_word_in_g_line(beg, &curs);
	}
	ft_memdel((void**)&beg);
	return (ret);
}
