/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_bin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:16 by fpasquer          #+#    #+#             */
/*   Updated: 2017/01/29 16:03:49 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static int					add_word_to_g_line(char **ret, char *beggin)
{
	char					*tmp;
	size_t					i;
	size_t					len_ret;
	t_line					*curs;

	if (ret == NULL || beggin == NULL || (curs = g_curs) == NULL)
		return (ERROR);
	tmp = *ret;
	if (tmp == NULL || (len_ret = ft_strlen(tmp)) == 0)
	{
		if (insert_word_in_g_line(beggin, &curs) == ERROR)
			return (ERROR);
		return (false);
	}
	i = 0;
	if (tmp[i] != '\0')
		if (insert_word_in_g_line(&tmp[i], &curs) == ERROR)
			return (ERROR);
	ft_memdel((void**)ret);
	return (true);
}

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
		char *beggin, t_bin *dico)
{
	char					**list_match;
	size_t					len_word;
	unsigned int			i;
	t_bin					*curs;

	if (y == 0 || beggin == NULL || (curs = dico) == NULL)
		return (NULL);
	if ((len_word = ft_strlen(beggin)) == 0)
		return (0);
	if ((list_match = ft_memalloc(sizeof(*list_match) * (y + 1))) == NULL)
		return (NULL);
	i = 0;
	while (curs != NULL)
	{
		if (ft_strncmp(curs->name, beggin, len_word) == 0)
			if ((list_match[i++] = ft_strdup(curs->name)) == NULL)
				return (list_match);
		curs = curs->n_dico;
	}
	return (list_match);
}

static int					put_autocompletion_bin(char *beggin, int i)
{
	char					**list_match;
	char					*ret;
	unsigned int			nb_match_word;
	t_bin					*dico;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (i < 0 || i >= SIZE_DICO || beggin == NULL || beggin[0] == '\0' ||
			(dico = sh->dico[i]) == NULL)
		return (ERROR);
	nb_match_word = get_nb_match_word(dico, beggin);
	if ((list_match = make_list_match(nb_match_word, beggin, dico)) == NULL)
																				{
																					DEBUG;
		return (nb_match_word == 0 ? false : ERROR);
																				}
	ret = print_list_term(sh, list_match, true);
																				//fprintf(debug, "nb_match_word = %u ret = '%s'\n", nb_match_word, ret);
	ft_free_strsplit(list_match);
	return (add_word_to_g_line(&ret, beggin));
}

static int					is_end_loop(t_entry *c)
{
	if (c == NULL || c->c == ' ' || c->c == ';')
		return (false);
	return (true);
}

static int					del_car_beggin_in_g_line(size_t len)
{
	if (g_curs == NULL)
		return (ERROR);
	g_curs->curs = g_curs->line;
	while (g_curs->curs != NULL && g_curs->curs->next != NULL)
		g_curs->curs = g_curs->curs->next;
	while (g_curs->curs != NULL && g_curs->curs->c == ' ')
		del_left();
																				//fprintf(debug, "len = %3zu line : %d\n", len, __LINE__);
	del_left();
	len--;
	while (len > 0)
	{
		del_left();
																				//fprintf(debug, "len = %3zu line : %d\n", len, __LINE__);
		len--;
	}
	return (true);
}

static char					*get_beggin_bin(t_entry *c)
{
	char					*beggin;
	size_t					len;
	size_t					mem_len;
	t_entry					*curs;

	if ((curs = c) == NULL)
		return (NULL);
	len = 0;
	while (is_end_loop(curs))
	{
		len++;
		curs = curs->prev;
	}
	if (len == 0)
		return (NULL);
	if ((beggin = ft_memalloc(sizeof(beggin) * (len + 1))) == NULL)
		return (NULL);
	mem_len = len;
	while (is_end_loop(c))
	{
		beggin[--len] = c->c;
		c = c->prev;
	}
	return (del_car_beggin_in_g_line(mem_len) == ERROR ? NULL : beggin);
}

int							autocompletion_bin(t_entry *c)
{
	char					*beg;
	int						i;
	int						ret;
	t_line					*curs;

	if ((curs = g_curs) == NULL)
		return (ERROR);
	if ((beg = get_beggin_bin(c)) == NULL)
		return (ERROR);
	if ((beg[0] >= 'a' && beg[0] <= 'z') || (beg[0] >= 'A' && beg[0] <= 'Z'))
		i = (beg[0] >= 'a' && beg[0] <= 'z') ? beg[0] - 'a' : beg[0] - 'A';
	else
		i = SIZE_DICO - 1;
																				//fprintf(debug, "beggin = '%s' i = %i\n", beg, i);
	if ((ret = put_autocompletion_bin(beg, i)) == false)
	{
																					DEBUG;
		place_curs();
		insert_word_in_g_line(beg, &curs);
	}
	ft_memdel((void**)&beg);
	return (ret);
}
