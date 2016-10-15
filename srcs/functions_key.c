/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 14:46:02 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/15 12:46:00 by fpasquer         ###   ########.fr       */
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

int							print_history_up(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (sh->hist != NULL && sh->hist->curs == NULL)
	{
		if ((sh->hist->curs = sh->hist) == NULL)
			return (false);
	}
	else if (sh->hist != NULL)
	{
		if (sh->hist->curs->next != NULL)
			sh->hist->curs = sh->hist->curs->next;
	}
	if (put_cmd_term("rc") == -1 || put_cmd_term("cd") == -1)
		return (false);
	del_g_lines();
	print_prompt();
	if (sh->hist != NULL && sh->hist->curs != NULL && sh->hist->curs->line != NULL)
	{
		ft_putstr(sh->hist->curs->line);
		insert_word_in_g_line(sh->hist->curs->line);
	}
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
	if (sh->hist != NULL && sh->hist->curs != NULL && sh->hist->curs->line != NULL)
	{
		ft_putstr(sh->hist->curs->line);
		insert_word_in_g_line(sh->hist->curs->line);
	}
	return (true);
}
