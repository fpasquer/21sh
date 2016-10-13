/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:45:29 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/13 17:55:09 by fpasquer         ###   ########.fr       */
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

static int				put_word(t_list_print *curs, int len,
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
	char					*cpy_word;
	t_21sh					*sh;

	if (word == NULL)
		return (ERROR);
	print_prompt();
	ft_putendl(word);
	ft_putstr(COLOR_LINE);
	if (end == false)
	{
		ft_putstr("recherches");
		ft_putendl(RESET_COLOR);
	}
	else
	{
		if ((sh = get_21sh(NULL)) == NULL)
			return (ERROR);
		ft_putstr(word);
		ft_putendl(RESET_COLOR);
		if ((cpy_word = ft_strdup(word)) == NULL)
			return (ERROR);
		if (exe_cmd(&sh->hist, &cpy_word) == ERROR)
			return (ERROR);
	}
	return (true);
}

static char					*print_words(t_list_print *lst, int  len,
		int nb_word_line,t_21sh  *sh)
{
	int						x;
	int						y;
	t_list_print			*curs;

	if (lst == NULL || len <= 0 || nb_word_line <= 0 ||
			print_prompt_word(lst->curs->word, false) == ERROR)
		return (NULL);
	curs = lst;
	y = 0;
	while (curs != NULL && (x = 0) == 0)
	{
		while (curs != NULL && x++ < nb_word_line)
		{
			if (put_word(curs, len ,lst) == ERROR)
				return (NULL);
			curs = curs->next;
		}
		ft_putchar('\n');
		y++;
	}
	return (put_curs(y, &lst->word));
	return (NULL);
}

int							put_cmd_term(char *cmd)
{
	char					*ret;

	if ((ret = tgetstr(cmd, NULL)) == NULL)
		return (ERROR);
	tputs(ret, 0, my_out_put);
	return (true);
}


char						*put_words_event(t_list_print *l, int  len,
		int nb_word_line,t_21sh  *sh)
{
	char					*ret;
	char					b[SIZE_BUFF];

	if (put_cmd_term("vi") == ERROR)
		return (NULL);
	if (l == NULL || len <= 0 || nb_word_line <= 0)
		return (NULL);
	l->curs = l;
	while ((ret = print_words(l, len, nb_word_line, sh)) != NULL)
	{
		ft_bzero(b, sizeof(b));
		if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0 || put_cmd_term("cd") == -1
				|| ENTER  || ESC)
			break ;
		l->curs = (ARROW_UP) && (l->curs->prev) ? l->curs->prev : l->curs;
		l->curs = (ARROW_DOWN) && (l->curs->next) ? l->curs->next : l->curs;
	}
	if (put_cmd_term("ve") == ERROR ||
			print_prompt_word(l->curs->word, true) == ERROR)
		return (NULL);
	return ((ESC) ? NULL : ret);
}

	/*	if (ARROW_UP)
			if (lst->curs->prev != NULL)
				lst->curs = lst->curs->prev;*/
		/*if (ARROW_DOWN)
			if (lst->curs->next != NULL)
				lst->curs = lst->curs->next;*/
