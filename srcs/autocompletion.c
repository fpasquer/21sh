/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 08:45:06 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/20 09:25:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

#define QUOTE 2
#define D_QUOTE 3
#define NONE 0
#define BIN 9
#define PATH 8

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

int							put_pompt_word(char **word)
{
	if (word == NULL)
		return (ERROR);
	print_prompt();
	print_g_line();
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

static char					*put_new_line(char *line, int mem)
{
	int						i;

	if (line == NULL || mem < 0)
		return (NULL);
	i = 0;
	while (i < mem)
		if (add_c_to_line(line[i++]) == ERROR)
			return (NULL);
	return (ft_strdup(&line[mem]));
}

static char					*get_new_line(char *line)
{
	char					*tmp;
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
	return (put_new_line(line, mem));
}

int							search_bin_path(char *line)
{
	char					*new_line;
	int						i;
	size_t					len;

	if (line == NULL)
		return (ERROR);
	i = 0;
	while (ft_isspace(line[i]) == true)
		i++;
	new_line = &line[i];
	if ((len = ft_strlen(new_line)) > 0)
	{
		while (len-- > 0)
			if (new_line[len] == ' ' || new_line[len] == '/')
				return (PATH);
		return (BIN);
	}
	return (false);
}

int							autocompletion_bin(t_21sh *sh, char *new_line)
{
	unsigned int			i;
	unsigned int			start;

	if (new_line == NULL)
		return (ERROR);
	start = 0;
	while (ft_isspace(new_line[start]) == true)
		start++;
	if (new_line[start] == '\0')
		return (false);
	if (new_line[start] >= 'a' && new_line[start] <= 'z')
		i = new_line[start] - 'a';
	else if (new_line[start] >= 'A' && new_line[start] <= 'Z')
		i = new_line[start] - 'A';
	else
		i = SIZE_DICO - 1;
	if (put_autocompletion(&new_line[start], sh, i) == ERROR)
		return (ERROR);
	return (true);
}

int							list_bin(char *path)
{
	char					*end;
	char					*curs;
	char					*begin_name;
	int						ret;

	if (path == NULL)
		return (ERROR);
	if ((end = ft_strrchr(path, '/')) == NULL)
		end = path;
	else
		end++;
	ret = ERROR;
	curs = path;
	while (curs < end)
		if (add_c_to_line(*curs++) == ERROR)
			return (ERROR);
	if ((begin_name = ft_strdup(curs)) == NULL)
		return (ERROR);
	*curs = '\0';
	if (path[0] == '\0')
		ret = list_all_bin("./", begin_name);
	else
		ret = list_all_bin(path, begin_name);
	ft_memdel((void**)&begin_name);
	return (ret);
}

int							autocompletion_path(t_21sh *sh, char *new_line)
{
	char					*path;
	int						i;
	int						end;
	int						ret;

	if (sh == NULL || new_line == NULL)
		return (ERROR);
	end = ft_strlen(new_line);
	while (end > 0)
		if (new_line[--end] == ' ')
			break ;
	i = 0;
	if (new_line[end] == ' ')
		end++;
	while (i < end)
		if (add_c_to_line(new_line[i++]) == ERROR)
			return (ERROR);
	if ((path = ft_strdup(&new_line[end])) == NULL)
		return (ERROR);
	ret = list_bin(path);
	ft_memdel((void**)&path);
	return (ret);
}

int							autocompletion(void)
{
	char					*line;
	char					*new_line;
	int						ret;
	t_21sh					*sh;

	if ((line = make_tab()) == NULL)
		return (ERROR);
	del_g_lines();
	if (line[0] == '\0' || (sh = get_21sh(NULL)) == NULL)
	{
		ft_memdel((void**)&line);
		return (false);
	}
	if ((new_line = get_new_line(line)) == NULL)
		return (ERROR);
	if ((ret = search_bin_path(new_line)) == BIN)
		ret = autocompletion_bin(sh, new_line);
	else if (ret == PATH)
		ret = autocompletion_path(sh, new_line);
	ft_memdel((void**)&new_line);
	ft_memdel((void**)&line);
	return (ret);
}
