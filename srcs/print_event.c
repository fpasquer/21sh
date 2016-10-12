/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:45:29 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/12 22:06:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"
#include <term.h>

#define COLOR_SELECT "\033[30;47"

static bool					g_curs = true;

static char					*put_curs(int y, char **ret)
{
	if (ret == NULL || *ret == NULL)
		return (NULL);
	put_cmd_term("rc");
	while (y-- > 0 && g_curs == true)
		if (put_cmd_term("up") == ERROR)
			return (NULL);
	g_curs = true;
	return (*ret);
}

static int				put_word(t_list_print *curs, int len,
		t_list_print *lst)
{
	int						i;

	if (curs == NULL || len <= 0 || lst == NULL || curs->word == NULL || lst->curs == NULL)
		return (ERROR);
	i = ft_strlen(curs->word);
	if (curs != lst->curs)
	{
		ft_putstr(COLOR_LINE);
		ft_putstr(curs->word);
		ft_putstr(RESET_COLOR);
	}
	else
		ft_putstr(curs->word);
	while (i++ < len)
		ft_putchar(' ');
	return (true);
}

static char					*print_words(t_list_print *lst, int  len,
		int nb_word_line,t_21sh  *sh)
{
	int						x;
	int						y;
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
			if (put_word(curs, len ,lst) == ERROR)
				return (NULL);
			curs = curs->next;
		}
		ft_putchar('\n');
		y++;
	}
	return (put_curs(y, &lst->word));
}

int							put_cmd_term(char *cmd)
{
	char					*ret;

	if ((ret = tgetstr(cmd, NULL)) == NULL)
		return (ERROR);
	tputs(ret, 0, my_out_put);
	return (true);
}


char						*put_words_event(t_list_print *lst, int  len,
		int nb_word_line,t_21sh  *sh)
{
	char					*ret;
	char					b[SIZE_BUFF];

	//if (put_cmd_term("vi") == ERROR)
	//	return (NULL);
	g_curs = true;
	if (lst == NULL || len <= 0 || nb_word_line <= 0)
		return (NULL);
	lst->curs = lst;
	while ((ret = print_words(lst, len, nb_word_line, sh)) != NULL)
	{
		ft_bzero(b, sizeof(b));
		if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0 || put_cmd_term("cd") == -1 ||  ESC)
			break ;
		if (ARROW_UP)
			if (lst->curs->prev != NULL)
				lst->curs = lst->curs->prev;
		if (ARROW_DOWN)
			if (lst->curs->next != NULL)
				lst->curs = lst->curs->next;
	}
	if (put_cmd_term("ve") == ERROR)
		return (NULL);
	return (NULL);
}
