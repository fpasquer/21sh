/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:01:47 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/24 18:12:37 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H

# define KEY_H

# include "shell_21sh.h"

# define MAX_LEN_LINE 10
# define SIZE_BUFF 8
# define SIZE_MEM 2000
# define BZ b[0] ==
# define B1 b[1] ==
# define B2 b[2] ==
# define B3 b[3] ==
# define B4 b[4] ==
# define B5 b[5] ==

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
**	h_srch :			si mode search history est actif ? 1 : 0
**	hdc :				si heredoc active ? 1 : 0
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
	bool					hdc;
}							t_line;

t_line						*g_lines;
t_line						*g_curs;
size_t						g_y;
size_t						g_x;

# define DS					(BZ -62 && B1 -89 && B2 83 && B3 0 && B4 0 && B5 0)
# define PLUS_MINUS			(BZ -62 && B1 -79 && B2 0 && B3 0 && B4 0 && B5 0)

# define TAB				(BZ 9 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define ENTER				(BZ 10 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define ESC				(BZ 27 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)

# define F1					(BZ 27 && B1 79 && B2 80 && B3 0 && B4 0 && B5 0)
# define F2					(BZ 27 && B1 79 && B2 81 && B3 0 && B4 0 && B5 0)
# define F3					(BZ 27 && B1 79 && B2 82 && B3 0 && B4 0 && B5 0)
# define F4					(BZ 27 && B1 79 && B2 83 && B3 0 && B4 0 && B5 0)
# define F5					(BZ 27 && B1 91 && B2 49 && B3 53 && B4 126 && B5 0)
# define F6					(BZ 27 && B1 91 && B2 49 && B3 55 && B4 126 && B5 0)
# define F7					(BZ 27 && B1 91 && B2 49 && B3 56 && B4 126 && B5 0)
# define F8					(BZ 27 && B1 91 && B2 49 && B3 57 && B4 126 && B5 0)
# define F13				(BZ 27 && B1 91 && B2 49 && B3 59 && B4 50 && B5 80)
# define F14				(BZ 27 && B1 91 && B2 49 && B3 59 && B4 50 && B5 81)
# define F15				(BZ 27 && B1 91 && B2 49 && B3 59 && B4 50 && B5 82)
# define F9					(BZ 27 && B1 91 && B2 50 && B3 48 && B4 126 && B5 0)
# define F10				(BZ 27 && B1 91 && B2 50 && B3 49 && B4 126 && B5 0)

# define CTRL_D				(BZ 4 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)

# define ARROW_UP			(BZ 27 && B1 91 && B2 65 && B3 0 && B4 0 && B5 0)
# define ARROW_DOWN			(BZ 27 && B1 91 && B2 66 && B3 0 && B4 0 && B5 0)
# define ARROW_RIGHT		(BZ 27 && B1 91 && B2 67 && B3 0 && B4 0 && B5 0)
# define ARROW_LEFT			(BZ 27 && B1 91 && B2 68 && B3 0 && B4 0 && B5 0)
# define HOME				(BZ 27 && B1 91 && B2 72 && B3 0 && B4 0 && B5 0)
# define END				(BZ 27 && B1 91 && B2 70 && B3 0 && B4 0 && B5 0)
# define SHIFT_UP			(BZ 27 && B1 91 && B2 49 && B3 59 && B4 50 && B5 65)
# define SHIFT_DOWN			(BZ 27 && B1 91 && B2 49 && B3 59 && B4 50 && B5 66)
# define SHIFT_LEFT			(BZ 27 && B1 91 && B2 49 && B3 59 && B4 50 && B5 68)
# define SHIFT_RIGHT		(BZ 27 && B1 91 && B2 49 && B3 59 && B4 50 && B5 67)
# define SEL_MOD			(BZ 20 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define CPY				(BZ 12 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define CUT				(BZ 21 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define PAST				(BZ 16 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define H_SRCH				(BZ 18 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)

# define SPACE				(BZ 32 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define EXCLAM_MACK		(BZ 33 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define INVERTED_COMMA		(BZ 34 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define SHARP				(BZ 35 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define DOLLAR				(BZ 36 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define PERCENT			(BZ 37 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define AND				(BZ 38 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define APOSTROPHE			(BZ 39 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define BRACKET_OPEN		(BZ 40 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define BRACKET_CLOSE		(BZ 41 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define STAR				(BZ 42 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define PLUS				(BZ 43 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define COMMA				(BZ 44 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define CM					(BZ 45 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define POINT				(BZ 46 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define SLACH				(BZ 47 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C0					(BZ 48 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C1					(BZ 49 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C2					(BZ 50 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C3					(BZ 51 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C4					(BZ 52 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C5					(BZ 53 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C6					(BZ 54 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C7					(BZ 55 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C8					(BZ 56 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define C9					(BZ 57 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define TWO_POINTS			(BZ 58 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define SEMICOLUM			(BZ 59 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LEFT				(BZ 60 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define EGA				(BZ 61 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define RIGHT				(BZ 62 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define QUESTION_MACK		(BZ 63 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define AT					(BZ 64 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HA					(BZ 65 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HB					(BZ 66 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HC					(BZ 67 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HD					(BZ 68 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HE					(BZ 69 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HF					(BZ 70 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HG					(BZ 71 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HH					(BZ 72 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HI					(BZ 73 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HJ					(BZ 74 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HK					(BZ 75 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HL					(BZ 76 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HM					(BZ 77 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HN					(BZ 78 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HO					(BZ 79 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HP					(BZ 80 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HQ					(BZ 81 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HR					(BZ 82 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HS					(BZ 83 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HT					(BZ 84 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HU					(BZ 85 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HV					(BZ 86 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HW					(BZ 87 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HX					(BZ 88 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HY					(BZ 89 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HZ					(BZ 90 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HOOK_OPEN			(BZ 91 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define BACKSLACH			(BZ 92 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define HOOK_CLOSE			(BZ 93 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define CIRCONFLEX			(BZ 94 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define UNDERSCORE			(BZ 95 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define GRAVE_ACCENT		(BZ 96 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LA					(BZ 97 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LB					(BZ 98 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LC					(BZ 99 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LD					(BZ 100 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LE					(BZ 101 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LF					(BZ 102 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LG					(BZ 103 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LH					(BZ 104 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LI					(BZ 105 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LJ					(BZ 106 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LK					(BZ 107 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LL					(BZ 108 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LM					(BZ 109 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LN					(BZ 110 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LO					(BZ 111 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LP					(BZ 112 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LQ					(BZ 113 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LR					(BZ 114 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LS					(BZ 115 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LT					(BZ 116 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LU					(BZ 117 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LV					(BZ 118 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LW					(BZ 119 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LX					(BZ 120 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LY					(BZ 121 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define LZ					(BZ 122 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define BRASE_OPEN			(BZ 123 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define PIPE				(BZ 124 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define BRASE_CLOSE		(BZ 125 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define TILD				(BZ 126 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define DEL				(BZ 127 && B1 0 && B2 0 && B3 0 && B4 0 && B5 0)
# define DEL_R				(BZ 27 && B1 91 && B2 51 && B3 126 && B4 0 && B5 0)

char						*get_line_entree(bool srch);
int							add_c_to_line(char c, t_line **lines);
int							insert_word_in_g_line(char *word, t_line **line);
int							save_y_x();
char						*make_tab(void);
void						del_g_lines(void);
int							get_infos_words(t_list_print *list,
		size_t *bigger_word, unsigned int *len_total, unsigned int *nb_word);
char						**make_list_object(char *path, char *begin_name,
		int count);

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

int							check_words_builtins_exclame(char c);

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
char						*get_begin_bin(t_entry *c);
int							get_infos_words(t_list_print *list,
		size_t *bigger_word, unsigned int *len_total, unsigned int *nb_word);
int							add_list_term(t_list_print **lst, char **word);

char						get_char_keyboard(void);
#endif
