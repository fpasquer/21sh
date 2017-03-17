/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char_keybord.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 19:15:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/17 19:21:29 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"

#define KEY_IGNORE -2
#define GC_ACTVT g_curs->activity == true
#define GC_ACTVT_NO g_curs->activity == false

static char					cmd_keyboard_2(char b[SIZE_BUFF])
{
	if (GC_ACTVT_NO && ESC)
		key_exit(EXIT_SUCCESS);
	else if (ARROW_RIGHT)
		return (move_right());
	else if (ARROW_LEFT)
		return (move_left());
	else if (SEL_MOD)
		return (selec_mode());
	else if (HOME)
		return (move_start_line());
	else if (END)
		return (move_end_line());
	else if (SHIFT_UP)
		return (line_up());
	else if (SHIFT_DOWN)
		return (line_down());
	else if (SHIFT_LEFT)
		return (word_left());
	else if (SHIFT_RIGHT)
		return (word_right());
	else if (CPY)
		return (cpy_event());
	return (KEY_IGNORE);
}

static char					cmd_keyboard(char b[SIZE_BUFF])
{
	if (GC_ACTVT_NO && ((b[0] >= 32 && b[0] <= 126) || ENTER))
		return (b[0]);
	else if (cmd_keyboard_2(b) != KEY_IGNORE)
		return (KEY_IGNORE);
	else if (GC_ACTVT_NO && F1)
		key_del_hist();
	else if (GC_ACTVT_NO && ARROW_UP)
		print_history_up();
	else if (GC_ACTVT_NO && ARROW_DOWN)
		print_history_down();
	else if (GC_ACTVT_NO && TAB)
		autocompletion();
	else if (GC_ACTVT_NO && PAST)
		past_event();
	else if (GC_ACTVT_NO && DEL)
		del_left();
	else if (GC_ACTVT_NO && DEL_R)
		del_right();
	else if (GC_ACTVT && (DEL || DEL_R))
		del_selec();
	else if (GC_ACTVT && CUT)
		cut_event();
	return (KEY_IGNORE);
}

char						get_char_keyboard(void)
{
	char					b[SIZE_BUFF];

	ft_bzero(b, sizeof(b));
	if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0)
		return (ERROR);
	return (cmd_keyboard(b));
}
