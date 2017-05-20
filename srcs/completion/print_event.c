/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:43:19 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/20 19:28:31 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>

#define COLOR_SELECT "\033[7m"

static char					*put_curs(int y, char **ret)
{
	if (ret == NULL || *ret == NULL)
		return (NULL);
	while (y-- + 2 > 0)
		if (put_cmd_term("up") == ERROR)
			return (NULL);
	return (*ret);
}

static int					put_word(t_list_print *curs, int len,
		t_list_print *lst)
{
	int						i;

	if (curs == NULL || len <= 0 || lst == NULL || curs->word == NULL ||
			lst->curs == NULL)
		return (ERROR);
	i = ft_strlen(curs->word);
	if (curs == lst->curs)
	{
		ft_putstr(COLOR_SELECT);
		ft_putstr(curs->word);
		ft_putstr(RESET_COLOR);
	}
	else
		ft_putstr(curs->word);
	while (i++ < len)
		ft_putchar(' ');
	return (true);
}

static int					print_prompt_word(char *word, bool end)
{
	size_t					len;
	t_21sh					*sh;

	if (word == NULL || (sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	len = ft_strlen(word);
	g_lines->y = (len + sh->len_prompt + g_lines->len) / sh->win.ws_col;
	if (end == false)
	{
		print_prompt();
		print_g_line();
		ft_putstr(word);
		ft_putstr(COLOR_LINE);
		ft_putstr("\nrecherches");
		ft_putendl(RESET_COLOR);
	}
	return (true);
}

static char					*print_words(t_list_print *lst, int len,
		int nb_word_line)
{
	int						x;
	int						y;
	t_list_print			*curs;

	if (lst == NULL || len <= 0 || nb_word_line <= 0 ||
			print_prompt_word(lst->curs->word, false) == ERROR)
		return (NULL);
	curs = lst;
	y = g_lines->y;
	while (curs != NULL && (x = 0) == 0)
	{
		while (curs != NULL && x++ < nb_word_line)
		{
			if (put_word(curs, len, lst) == ERROR)
				return (NULL);
			curs = curs->next;
		}
		ft_putchar('\n');
		y++;
	}
	return (put_curs(y, &lst->word));
}

char						*put_words_event(t_list_print *l, int len,
		int nb_word_line)
{
	char					*ret;
	char					b[SIZE_BUFF];

	if (put_cmd_term("vi") == ERROR || put_cmd_term("rc") == ERROR)
		return (NULL);
	if (l == NULL || len <= 0 || nb_word_line <= 0)
		return (NULL);
	l->curs = l;
	while ((ret = print_words(l, len, nb_word_line)) != NULL)
	{
		ft_bzero(b, sizeof(b));
		if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0 || put_cmd_term("cd") == -1
				|| ENTER || ESC)
			break ;
		l->curs = (ARROW_LEFT) && (l->curs->prev) ? l->curs->prev : l->curs;
		l->curs = (ARROW_RIGHT) && (l->curs->next) ? l->curs->next : l->curs;
		l->curs = (TAB) && (l->curs->next) ? l->curs->next : l->curs;
	}
	if (put_cmd_term("ve") == ERROR ||
			print_prompt_word(l->curs->word, true) == ERROR)
		return (NULL);
	return ((ESC) ? NULL : ft_strdup(l->curs->word));
}
