/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 14:46:02 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/18 12:54:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void						key_exit(unsigned char val_exit)
{
	ft_putendl(COLOR_LINE);
	ft_putstr("exit");
	ft_putendl(RESET_COLOR);
	del_21sh();
	exit(val_exit);
}

int							key_del_hist(void)
{
	ft_putendl(COLOR_LINE);
	ft_putstr("del history");
	ft_putendl(RESET_COLOR);
	del_hist();
	print_prompt();
	return (true);
}

static int					curs_history_up(t_21sh *sh, size_t len)
{
	size_t					mem;

	if (sh == NULL || sh->pos_prev < 0)
		return (ERROR);
	mem = len;
	len = len % sh->win.ws_col;
	mem = mem / sh->win.ws_col;
	len += sh->len_prompt;
	while (len-- > 0)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	while (mem-- > 0)
		if (put_cmd_term("up") == ERROR)
			return (ERROR);
	return (put_cmd_term("cd"));
}

int							print_history_up(void)
{
	size_t					len;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (sh->hist != NULL && sh->hist->curs == NULL)
	{
		if ((sh->hist->curs = sh->hist) == NULL)
			return (false);
	}
	else if (sh->hist != NULL)
		if (sh->hist->curs->next != NULL)
			sh->hist->curs = sh->hist->curs->next;
	len = g_lines.i;
	if (sh->hist != NULL && sh->hist->curs != NULL && sh->hist->curs->line != NULL)
	{
		del_g_lines();
		insert_word_in_g_line(sh->hist->curs->line);
	}
	if (curs_history_up(sh, len) == ERROR)
		return (ERROR);
	print_prompt();
	if (sh->hist != NULL && sh->hist->curs != NULL && sh->hist->curs->line != NULL)
		ft_putstr(sh->hist->curs->line);
	return (true);
}

int							mouve_righ(void)
{
	static bool				decalage;

	if (g_lines.i < g_lines.len)
	{
		if (put_cmd_term("nd") == ERROR && decalage == true)
			return (ERROR);
		if (g_lines.curs != NULL)
		{
			if (g_lines.curs->next != NULL)
				g_lines.curs = g_lines.curs->next;
		}
		else
			g_lines.curs = g_lines.line;
		g_lines.i++;
	}
	return (true);
}

int							mouve_left(void)
{
	if (g_lines.curs != NULL)
	{
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
		g_lines.curs = g_lines.curs->prev;
		g_lines.i--;
	}
	return (true);
}

static int					put_c(void)
{
	int						loop;
	t_entry					*start;

	loop = 0;
	start = g_lines.curs != NULL ? g_lines.curs->next : g_lines.line;
	while (start != NULL)
	{
		ft_putchar(start->c);
		loop++;
		start = start->next;
	}
	while (loop-- > 0)
		if (put_cmd_term("le") == ERROR)
			return (false);
	return (true);
}

int							del_right(void)
{
	t_entry					*curs_tmp;

	if (g_lines.curs != NULL)
	{
		if (put_cmd_term("le") == ERROR || put_cmd_term("cd") == ERROR)
			return (ERROR);
		if (g_lines.curs->next != NULL)
			g_lines.curs->next->prev = g_lines.curs->prev;
		if (g_lines.curs->prev != NULL)
			g_lines.curs->prev->next = g_lines.curs->next;
		if (g_lines.curs == g_lines.line)
			g_lines.line = g_lines.line->next;
		curs_tmp = g_lines.curs->prev;
		ft_memdel((void**)&g_lines.curs);
		g_lines.curs = curs_tmp;
		g_lines.i--;
		g_lines.len--;
		put_c();
	}
	return (true);
}

int							print_history_down(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (sh->hist != NULL && sh->hist->curs != NULL)
		sh->hist->curs = sh->hist->curs->prev;
	if (put_cmd_term("rc") == -1 || put_cmd_term("cd") == -1)
		return (false);
	del_g_lines();
	print_prompt();
	if (sh->hist != NULL && sh->hist->curs != NULL &&
			sh->hist->curs->line != NULL)
	{
		ft_putstr(sh->hist->curs->line);
		insert_word_in_g_line(sh->hist->curs->line);
	}
	return (true);
}

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
	if (put_autocompletion(line, sh, i) == ERROR)
		return (ERROR);
	ft_memdel((void**)&line);
	return (true);
}
