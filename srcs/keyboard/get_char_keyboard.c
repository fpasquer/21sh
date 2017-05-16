/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char_keybord.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 19:15:05 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/16 18:16:29 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/key.h"

#define KEY_IGNORE -2
#define GL_ACTVT g_lines->activity == true
#define GL_ACTVT_NO g_lines->activity == false
#define GL_SRCH g_lines->h_srch == true
#define GL_SRCH_NO g_lines->h_srch == false

static char					cmd_keyboard_2(char b[SIZE_BUFF])
{
	if (GL_ACTVT_NO && GL_SRCH_NO && CTRL_D)
		ctrl_d(EXIT_SUCCESS);
	else if (ARROW_RIGHT)
		return (move_right());
	else if (ARROW_LEFT)
		return (move_left());
	else if (GL_SRCH_NO && SEL_MOD)
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
	else if (GL_SRCH_NO && CPY)
		return (cpy_event());
	else if (GL_ACTVT && GL_SRCH_NO && CUT)
		return (cut_event());
	return (KEY_IGNORE);
}

static char					cmd_keyboard(char b[SIZE_BUFF])
{
	if (GL_ACTVT_NO && ((b[0] >= 32 && b[0] <= 126) || ENTER))
		return (b[0]);
	else if (cmd_keyboard_2(b) != KEY_IGNORE)
		return (KEY_IGNORE);
	else if (GL_ACTVT_NO && GL_SRCH_NO && H_SRCH)
		search_history();
	else if (GL_ACTVT_NO && GL_SRCH_NO && F1)
		key_del_hist();
	else if (GL_ACTVT_NO && GL_SRCH_NO && ARROW_UP)
		print_history_up();
	else if (GL_ACTVT_NO && GL_SRCH_NO && ARROW_DOWN)
		print_history_down();
	else if (GL_ACTVT_NO && GL_SRCH_NO && TAB)
		autocompletion();
	else if (GL_ACTVT_NO && GL_SRCH_NO && PAST)
		past_event();
	else if (GL_ACTVT_NO && DEL)
		del_left();
	else if (GL_ACTVT_NO && DEL_R)
		del_right();
	else if (GL_ACTVT && GL_SRCH_NO && (DEL || DEL_R))
		del_selec();
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
