/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 21:42:08 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/31 10:00:36 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void						key_exit(unsigned char val_exit)
{
	ft_putendl(COLOR_LINE);
	put_cmd_term("cd");
	ft_putstr("exit");
	ft_putendl(RESET_COLOR);
	del_g_lines();
	del_21sh();
	exit(val_exit);
}

int							key_del_hist(void)
{
	t_history					*next;
	t_21sh					*sh;

	ft_putendl(COLOR_LINE);
	ft_putstr("del history");
	ft_putendl(RESET_COLOR);
	if ((sh = get_21sh(NULL)) != NULL)
		while (sh->hist != NULL)
		{
			next = sh->hist->next;
			ft_memdel((void**)&sh->hist->line);
			ft_memdel((void**)&sh->hist);
			sh->hist = next;
		}
	print_prompt();
	return (true);
}


int							print_history_up(void)
{
	size_t					len;
	t_line					*curs;
	t_21sh					*sh;

	curs = g_lines;
	if ((sh = get_21sh(NULL)) == NULL || curs == NULL)
		return (curs == NULL ? false : ERROR);
	if (sh->hist != NULL && sh->hist->curs == NULL)
	{
		if ((sh->hist->curs = sh->hist) == NULL)
			return (false);
	}
	else if (sh->hist != NULL)
		if (sh->hist->curs->next != NULL)
			sh->hist->curs = sh->hist->curs->next;
	if (sh->hist != NULL && sh->hist->curs != NULL && sh->hist->curs->line != NULL)
	{
		while (curs->next != NULL)
			curs = curs->next;
		del_g_lines();
		insert_word_in_g_line(sh->hist->curs->line, &curs);
	}
	if (sh->hist != NULL && sh->hist->curs != NULL && sh->hist->curs->line != NULL)
		ft_putstr(sh->hist->curs->line);
	return (true);
}
