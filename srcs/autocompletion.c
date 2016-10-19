/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 08:45:06 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/19 09:55:46 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

#define QUOTE 2
#define D_QUOTE 3
#define NONE 0

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

static int					get_new_i(char *l, int *i, int *mem)
{
	if (l == NULL || *i < 0 || mem == NULL)
		return (ERROR);
	if (ft_strncmp(&l[*i], "||", 2) == 0 || ft_strncmp(&l[*i], "&&", 2) == 0)
	{
		*i = *i + 2;
		while (ft_isspace(l[*i]) == true)
			*i = *i + 1;
		*mem = *i;
		return (true);
	}
	else if (l[*i] == ';')
	{
		*i = *i + 1;
		while (ft_isspace(l[*i]) == true)
			*i = *i + 1;
		*mem = *i;
		return (true);
	}
	else
		*i += 1;
	return (false);
}

static char					*is_autocompletion_bin(char *line)
{
	int						ignore;
	int						i;
	int						mem;

	if (line == NULL)
		return (NULL);
	ignore = NONE;
	i = 0;
	mem = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && (ignore == NONE || ignore == QUOTE))
			ignore = (ignore == NONE) ? QUOTE : NONE;
		if (line[i] == '\"' && (ignore == NONE || ignore == D_QUOTE))
			ignore = (ignore == NONE) ? D_QUOTE : NONE;
		if (ignore == NONE)
		{
			if (get_new_i(line, &i, &mem) == ERROR)
				return (NULL);
		}
		else
			i++;
	}
	return (ft_strdup(&line[mem]));
}

int							autocompletion(void)
{
	char					*line;
	char					*new_line;
	unsigned int			i;
	t_21sh					*sh;

	if ((line = make_tab()) == NULL)
		return (ERROR);
	if (line[0] == '\0' || (sh = get_21sh(NULL)) == NULL)
	{
		del_g_lines();
		ft_memdel((void**)&line);
		return (false);
	}
	if ((new_line = is_autocompletion_bin(line)) == NULL)
		return (ERROR);
	if (new_line[0] >= 'a' && new_line[0] <= 'z')
		i = new_line[0] - 'a';
	else if (new_line[0] >= 'A' && new_line[0] <= 'Z')
		i = new_line[0] - 'A';
	else
		i = SIZE_DICO - 1;
	if (put_autocompletion(new_line, sh, i) == ERROR)
		return (ERROR);
	ft_memdel((void**)&line);
	return (true);
}
