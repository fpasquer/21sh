/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 21:42:08 by fpasquer          #+#    #+#             */
/*   Updated: 2016/11/01 10:38:20 by fpasquer         ###   ########.fr       */
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
	char					*tab;
	int						ret;

	if ((tab = make_tab()) == NULL)
		return (ERROR);
	ret = search_history_up(tab);
	ft_memdel((void**)&tab);
	return (ret);
}

int							print_history_down(void)
{
	char					*tab;
	int						ret;

	if ((tab = make_tab()) == NULL)
		return (ERROR);
	ret = search_history_down(tab);
	ft_memdel((void**)&tab);
	return (ret);
}
