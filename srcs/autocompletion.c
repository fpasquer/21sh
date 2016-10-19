/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 08:45:06 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/19 08:47:20 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static unsigned int			nb_match_word(t_bin *lst, char *word)
{
	unsigned int			nb_match;
	size_t					len_word;
	t_bin					*curs;

	if (word == NULL)
		return (0);
	nb_match = 0;
	curs = lst;
	len_word = ft_strlen(word);
	while (curs != NULL)
	{
		if (ft_strncmp(curs->name, word, len_word) == 0)
			nb_match++;
		curs = curs->n_dico;
	}
	return (nb_match);
}

static char					**make_tab_list(t_bin *lst, unsigned int y,
		char *word)
{
	char					**tab;
	unsigned int			i;
	size_t					len_word;
	t_bin					*curs;

	if (y == 0 || word == NULL)
		return (NULL);
	if ((tab = ft_memalloc(sizeof(*tab) * (y + 1))) == NULL)
		return (NULL);
	i = 0;
	curs = lst;
	if ((len_word = ft_strlen(word)) == 0)
		return (NULL);
	while (curs != NULL)
	{
		if (ft_strncmp(curs->name, word, len_word) == 0)
			if ((tab[i++] = ft_strdup(curs->name)) == NULL)
				break ;
		curs = curs->n_dico;
	}
	return (tab);
}

static int					put_pompt_word(char **word)
{
	if (word == NULL)
		return (ERROR);
	print_prompt();
	if (*word != NULL)
	{
		insert_word_in_g_line(*word);
		ft_putstr(*word);
		ft_memdel((void**)word);
	}
	return (true);
}

static int					put_autocompletion(char *line, t_21sh *sh,
		unsigned int i)
{
	char					**list;
	char					*ret;
	unsigned int			loop;
	t_bin					*curs;

	if (line == NULL || sh == NULL)
		return (ERROR);
	if ((loop = nb_match_word(sh->dico[i], line)) <= 0)
	{
		insert_word_in_g_line(line);
		return (false);
	}
	if ((list = make_tab_list(sh->dico[i], loop, line)) == NULL)
		return (ERROR);
	ret = print_list_term(sh, list, true);
	ft_free_strsplit(list);
	return (put_pompt_word(&ret));
}

int							autocompletion(void)
{
	char					*line;
	unsigned int			i;
	t_21sh					*sh;

	if ((line = make_tab()) == NULL)
		return (ERROR);
	if (line[0] == '\0' || (sh = get_21sh(NULL)) == NULL)
	{
		ft_memdel((void**)&line);
		return (false);
	}
	if (line[0] >= 'a' && line[0] <= 'z')
		i = line[0] - 'a';
	else if (line[0] >= 'A' && line[0] <= 'Z')
		i = line[0] - 'A';
	else
		i = SIZE_DICO - 1;
	del_g_lines();
	if (put_autocompletion(line, sh, i) == ERROR)
		return (ERROR);
	ft_memdel((void**)&line);
	return (true);
}
