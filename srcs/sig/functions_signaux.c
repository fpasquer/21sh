/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_signaux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:30:40 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/03 17:58:00 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

void						resize_win(int val)
{
	t_21sh					*sh;

	val = val + 0;
	if ((sh = get_21sh(NULL)) != NULL)
		ioctl(0, TIOCGWINSZ, &sh->win);
}

static void					retake_entree(int signum)
{
	if (signum == SIGINT)
		;
}

static void					suspend_and_continue(int signum)
{
	if (signum == SIGCONT)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &((get_21sh(NULL))->term_param));
}

void						ctrl_d(int val)
{
	if (g_curs != NULL)
	{
		if (g_curs->line == NULL)
			key_exit(val);
		else
			del_right();
	}
}

void						sig_manager(void)
{
	signal(SIGWINCH, resize_win);
	signal(SIGINT, retake_entree);
	signal(SIGCONT, suspend_and_continue);
}
