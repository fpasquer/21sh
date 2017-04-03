/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:01:47 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/03 19:26:24 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H

# define KEY_H

# include "shell_21sh.h"

# define MAX_LEN_LINE 10
# define SIZE_BUFF 8
# define SIZE_MEM 2000
# define b0 b[0] ==
# define b1 b[1] ==
# define b2 b[2] ==
# define b3 b[3] ==
# define b4 b[4] ==
# define b5 b[5] ==

/*
**	c :					carcatere de la commande
**	next :				maillon suivant de la de la commande
**	prev :				maillon precedent de la commande
*/
typedef struct				s_entry
{
	char					c;
	bool					select;
	struct s_entry			*next;
	struct s_entry			*prev;
}							t_entry;

/*
**	line :				premier maillon de la commade
**	curs :				position du maillon dans la commande
**	sel_start :			debut de la selection
**	sel_end :			fin de la selection
**	next :				si la commande est multi commande (avec des quotes)
**	len :				longueur de la commande
**	i :					position dans la commade
**	x :					position fin de ligne horizontalement
**	y :					decalage de ligne par rapport au prompt
**	x_i :				place du caracter horizontalement
**	y_i :				place du caracter verticalement
**	last_dir :			derniere direction employer dans le mode selec_mode
**	lft_rgt :			balance pr savoir si end et a gauche ou droit de start
**	activity :			si le selec_mode est actif ? 1 : 0
*/
typedef struct				s_line
{
	t_entry					*line;
	t_entry					*curs;
	t_entry					*sel_start;
	t_entry					*sel_end;
	struct s_line			*next;
	size_t					len;
	size_t					count_line;
	size_t					i;
	size_t					x;
	size_t					y;
	size_t					x_i;
	size_t					y_i;
	size_t					last_dir;
	int						lft_rgt;
	bool					activity;
	bool					h_srch;
}							t_line;

t_line						*g_lines;
t_line						*g_curs;
size_t						g_y;
size_t						g_x;

# define DS					(b0 -62 && b1 -89 && b2 83 && b3 0 && b4 0 && b5 0)
# define PLUS_MINUS			(b0 -62 && b1 -79 && b2 0 && b3 0 && b4 0 && b5 0)

# define TAB				(b0 9 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define ENTER				(b0 10 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define ESC				(b0 27 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)

# define F1					(b0 27 && b1 79 && b2 80 && b3 0 && b4 0 && b5 0)
# define F2					(b0 27 && b1 79 && b2 81 && b3 0 && b4 0 && b5 0)
# define F3					(b0 27 && b1 79 && b2 82 && b3 0 && b4 0 && b5 0)
# define F4					(b0 27 && b1 79 && b2 83 && b3 0 && b4 0 && b5 0)
# define F5					(b0 27 && b1 91 && b2 49 && b3 53 && b4 126 && b5 0)
# define F6					(b0 27 && b1 91 && b2 49 && b3 55 && b4 126 && b5 0)
# define F7					(b0 27 && b1 91 && b2 49 && b3 56 && b4 126 && b5 0)
# define F8					(b0 27 && b1 91 && b2 49 && b3 57 && b4 126 && b5 0)
# define F13				(b0 27 && b1 91 && b2 49 && b3 59 && b4 50 && b5 80)
# define F14				(b0 27 && b1 91 && b2 49 && b3 59 && b4 50 && b5 81)
# define F15				(b0 27 && b1 91 && b2 49 && b3 59 && b4 50 && b5 82)
# define F9					(b0 27 && b1 91 && b2 50 && b3 48 && b4 126 && b5 0)
# define F10				(b0 27 && b1 91 && b2 50 && b3 49 && b4 126 && b5 0)

# define CTRL_D				(b0 4 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)

# define ARROW_UP			(b0 27 && b1 91 && b2 65 && b3 0 && b4 0 && b5 0)
# define ARROW_DOWN			(b0 27 && b1 91 && b2 66 && b3 0 && b4 0 && b5 0)
# define ARROW_RIGHT		(b0 27 && b1 91 && b2 67 && b3 0 && b4 0 && b5 0)
# define ARROW_LEFT			(b0 27 && b1 91 && b2 68 && b3 0 && b4 0 && b5 0)
# define HOME				(b0 27 && b1 91 && b2 72 && b3 0 && b4 0 && b5 0)
# define END				(b0 27 && b1 91 && b2 70 && b3 0 && b4 0 && b5 0)
# define SHIFT_UP			(b0 27 && b1 91 && b2 49 && b3 59 && b4 50 && b5 65)
# define SHIFT_DOWN			(b0 27 && b1 91 && b2 49 && b3 59 && b4 50 && b5 66)
# define SHIFT_LEFT			(b0 27 && b1 91 && b2 49 && b3 59 && b4 50 && b5 68)
# define SHIFT_RIGHT		(b0 27 && b1 91 && b2 49 && b3 59 && b4 50 && b5 67)
# define SEL_MOD			(b0 20 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define CPY				(b0 12 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define CUT				(b0 21 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define PAST				(b0 16 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define H_SRCH				(b0 18 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)

# define SPACE				(b0 32 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define EXCLAM_MACK		(b0 33 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define INVERTED_COMMA		(b0 34 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define SHARP				(b0 35 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define DOLLAR				(b0 36 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define PERCENT			(b0 37 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define AND				(b0 38 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define APOSTROPHE			(b0 39 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define BRACKET_OPEN		(b0 40 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define BRACKET_CLOSE		(b0 41 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define STAR				(b0 42 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define PLUS				(b0 43 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define COMMA				(b0 44 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define CM					(b0 45 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define POINT				(b0 46 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define SLACH				(b0 47 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C0					(b0 48 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C1					(b0 49 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C2					(b0 50 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C3					(b0 51 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C4					(b0 52 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C5					(b0 53 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C6					(b0 54 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C7					(b0 55 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C8					(b0 56 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define C9					(b0 57 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define TWO_POINTS			(b0 58 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define SEMICOLUM			(b0 59 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LEFT				(b0 60 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define EGA				(b0 61 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define RIGHT				(b0 62 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define QUESTION_MACK		(b0 63 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define AT					(b0 64 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HA					(b0 65 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HB					(b0 66 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HC					(b0 67 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HD					(b0 68 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HE					(b0 69 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HF					(b0 70 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HG					(b0 71 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HH					(b0 72 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HI					(b0 73 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HJ					(b0 74 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HK					(b0 75 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HL					(b0 76 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HM					(b0 77 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HN					(b0 78 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HO					(b0 79 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HP					(b0 80 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HQ					(b0 81 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HR					(b0 82 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HS					(b0 83 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HT					(b0 84 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HU					(b0 85 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HV					(b0 86 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HW					(b0 87 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HX					(b0 88 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HY					(b0 89 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HZ					(b0 90 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HOOK_OPEN			(b0 91 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define BACKSLACH			(b0 92 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define HOOK_CLOSE			(b0 93 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define CIRCONFLEX			(b0 94 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define UNDERSCORE			(b0 95 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define GRAVE_ACCENT		(b0 96 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LA					(b0 97 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LB					(b0 98 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LC					(b0 99 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LD					(b0 100 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LE					(b0 101 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LF					(b0 102 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LG					(b0 103 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LH					(b0 104 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LI					(b0 105 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LJ					(b0 106 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LK					(b0 107 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LL					(b0 108 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LM					(b0 109 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LN					(b0 110 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LO					(b0 111 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LP					(b0 112 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LQ					(b0 113 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LR					(b0 114 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LS					(b0 115 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LT					(b0 116 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LU					(b0 117 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LV					(b0 118 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LW					(b0 119 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LX					(b0 120 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LY					(b0 121 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define LZ					(b0 122 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define BRASE_OPEN			(b0 123 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define PIPE				(b0 124 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define BRASE_CLOSE		(b0 125 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define TILD				(b0 126 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define DEL				(b0 127 && b1 0 && b2 0 && b3 0 && b4 0 && b5 0)
# define DEL_R				(b0 27 && b1 91 && b2 51 && b3 126 && b4 0 && b5 0)

char						*get_line_entree(bool srch);
int							add_c_to_line(char c, t_line **lines);
int							insert_word_in_g_line(char *word, t_line **line);
char						*make_tab(void);
void						del_g_lines(void);

void						key_exit(unsigned char val_exit);
int							key_del_hist(void);
int							print_history_up(void);
int							print_history_down(void);
int							search_history_up(char *beguin);
int							search_history_down(char *beguin);
int							move_right(void);
int							move_left(void);
int							del_left(void);
int							del_right(void);
int							place_curs(void);
int							put_cmd(void);
int							save_y_x_line(t_line **line);
int							put_lines(void);

char						last_c(t_line *line, size_t i);

int							line_up(void);
int							line_down(void);
int							word_left(void);
int							word_right(void);
int							move_start_line(void);
int							move_end_line(void);
int							selec_mode(void);
int							reset_selec(int ret);
int							selec_manager(size_t r_l);
int							cpy_event(void);
int							cut_event(void);
int							past_event(void);
int							del_selec(void);

int							autocompletion_bin(t_entry *c);
int							autocompletion_path(t_entry *c);

char						get_char_keyboard(void);
#endif
