/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 13:01:40 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/11 14:01:38 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H

# define KEY_H

#include "shell_21sh.h"

# define MAX_LEN_LINE 10
# define SIZE_BUFF 5

typedef struct				s_line
{
	char					line[MAX_LEN_LINE];
	unsigned int			i;
	struct s_line			*next;
}							t_line;


# define ESC				(b[0] ==  27 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //echap
# define F1					(b[0] ==  27 && b[1] ==  79 && b[2] ==  80 && b[3] ==   0 && b[4] ==   0) //f1
# define F2					(b[0] ==  27 && b[1] ==  79 && b[2] ==  81 && b[3] ==   0 && b[4] ==   0) //f2
# define F3					(b[0] ==  27 && b[1] ==  79 && b[2] ==  82 && b[3] ==   0 && b[4] ==   0) //f3
# define F4					(b[0] ==  27 && b[1] ==  79 && b[2] ==  83 && b[3] ==   0 && b[4] ==   0) //f4
# define F5					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  53 && b[4] == 126) //f5
# define F6					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  55 && b[4] == 126) //f6
# define F7					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  56 && b[4] == 126) //f7
# define F8					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  57 && b[4] == 126) //f8
# define F9					(b[0] ==  27 && b[1] ==  91 && b[2] ==  50 && b[3] ==  48 && b[4] == 126) //f9
# define F10				(b[0] ==  27 && b[1] ==  91 && b[2] ==  50 && b[3] ==  49 && b[4] == 126) //f10

/*
# define F11 () //f11 Ne fonctionne pas sur mon mac perso
# define F12 () //f12 Ne fonctionne pas sur mon mac perso
*/

# define DS					(b[0] == -62 && b[1] == -89 && b[2] ==  83 && b[3] ==   0 && b[4] ==   0) //§ au dessus de tab
# define C1					(b[0] ==  49 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //1 clavier
# define C2					(b[0] ==  50 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //2 clavier
# define C3					(b[0] ==  51 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //3 clavier
# define C4					(b[0] ==  52 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //4 clavier
# define C5					(b[0] ==  53 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //5 clavier
# define C6					(b[0] ==  54 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //6 clavier
# define C7					(b[0] ==  55 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //7 clavier
# define C8					(b[0] ==  56 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //8 clavier
# define C9					(b[0] ==  57 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //9 clavier
# define C0					(b[0] ==  48 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //0 clavier
# define CM					(b[0] ==  45 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //- clavier
# define EGA				(b[0] ==  61 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //= clavier
# define DEL				(b[0] == 127 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //<- del gauche

# define TAB				(b[0] ==   9 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //tabulation
# define LQ					(b[0] == 113 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //q
# define LW					(b[0] == 119 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //w
# define LE					(b[0] == 101 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //e
# define LR					(b[0] == 114 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //r
# define LT					(b[0] == 116 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //t
# define LY					(b[0] == 121 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //y
# define LU					(b[0] == 117 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //u
# define LI					(b[0] == 105 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //i
# define LO					(b[0] == 111 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //o
# define LP					(b[0] == 112 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //p
# define HOOK_OPEN			(b[0] ==  91 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //[
# define HOOK_CLOSE			(b[0] ==  93 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //]
# define ENTER				(b[0] ==  10 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //\n

# define LA					(b[0] ==  97 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //a
# define LS					(b[0] == 115 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //s
# define LD					(b[0] == 100 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //d
# define LF					(b[0] == 102 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //f
# define LG					(b[0] == 103 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //g
# define LH					(b[0] == 104 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //h
# define LJ					(b[0] == 106 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //j
# define LK					(b[0] == 107 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //k
# define LL					(b[0] == 108 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //l
# define SEMICOLUM			(b[0] ==  59 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //;
# define APOSTROPHE			(b[0] ==  39 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //'
# define BACKSLACH			(b[0] ==  92 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //'\'

# define GRAVE_ACCENT		(b[0] ==  96 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //`
# define LZ					(b[0] == 122 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //z
# define LX					(b[0] == 120 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //x
# define LC					(b[0] ==  99 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //c
# define LV					(b[0] == 118 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //v
# define LB					(b[0] ==  98 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //b
# define LN					(b[0] == 110 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //n
# define LM					(b[0] == 109 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //m
# define COMMA				(b[0] ==  44 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //,
# define POINT				(b[0] ==  46 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //.
# define SLACH				(b[0] ==  47 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) ///

# define SPACE				(b[0] ==  32 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //' '
# define ARROW_LEFT			(b[0] ==  27 && b[1] ==  91 && b[2] ==  68 && b[3] ==   0 && b[4] ==   0) //fleche gauche
# define ARROW_RIGHT		(b[0] ==  27 && b[1] ==  91 && b[2] ==  67 && b[3] ==   0 && b[4] ==   0) //fleche droite
# define ARROW_DOWN			(b[0] ==  27 && b[1] ==  91 && b[2] ==  66 && b[3] ==   0 && b[4] ==   0) //fleche bas
# define ARROW_UP			(b[0] ==  27 && b[1] ==  91 && b[2] ==  65 && b[3] ==   0 && b[4] ==   0) //fleche haut

# define PLUS_MINUS			(b[0] == -62 && b[1] == -79 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //±
# define EXCLAM_MACK		(b[0] ==  33 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //!
# define AT					(b[0] ==  64 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //@
# define SHARP				(b[0] ==  35 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //#
# define DOLLAR				(b[0] ==  36 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //$
# define PERCENT			(b[0] ==  37 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //%
# define CIRCONFLEX			(b[0] ==  94 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //^
# define AND				(b[0] ==  38 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //&
# define STAR				(b[0] ==  42 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //*
# define BRACKET_OPEN		(b[0] ==  40 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //(
# define BRACKET_CLOSE		(b[0] ==  41 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //)
# define UNDERSCORE			(b[0] ==  95 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //_
# define PLUS				(b[0] ==  43 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //+

# define HQ					(b[0] ==  81 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //Q
# define HW					(b[0] ==  87 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //W
# define HE					(b[0] ==  69 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //E
# define HR					(b[0] ==  82 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //R
# define HT					(b[0] ==  84 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //T
# define HY					(b[0] ==  89 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //Y
# define HU					(b[0] ==  85 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //U
# define HI					(b[0] ==  73 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //I
# define HO					(b[0] ==  79 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //O
# define HP					(b[0] ==  80 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //P
# define BRASE_OPEN			(b[0] == 123 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //{
# define BRASE_CLOSE		(b[0] == 125 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //}

# define HA					(b[0] ==  65 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //A
# define HS					(b[0] ==  83 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //S
# define HD					(b[0] ==  68 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //D
# define HF					(b[0] ==  70 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //F
# define HG					(b[0] ==  71 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //G
# define HH					(b[0] ==  72 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //H
# define HJ					(b[0] ==  74 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //J
# define HK					(b[0] ==  75 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //K
# define HL					(b[0] ==  76 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //L
# define TWO_POINTS			(b[0] ==  58 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //:
# define INVERTED_COMMA		(b[0] ==  34 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //"
# define PIPE				(b[0] == 124 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //|

# define TILD				(b[0] == 126 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //~
# define HZ					(b[0] ==  90 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //Z
# define HX					(b[0] ==  88 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //X
# define HC					(b[0] ==  67 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //C
# define HV					(b[0] ==  86 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //V
# define HB					(b[0] ==  66 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //B
# define HN					(b[0] ==  78 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //N
# define HM					(b[0] ==  77 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //M
# define LEFT				(b[0] ==  60 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //<
# define RIGHT				(b[0] ==  62 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //>
# define QUESTION_MACK		(b[0] ==  63 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0) //?


#define BUFF_SIZE_READ 5

char						*get_line_entree(void);
int							my_out_put(int c);
/*int							move_one_c_left(void);
int							move_one_c_right(void);
int							del_left(void);
char						*save_line(char c);
int							cmd_termcap(char *str);
char						*get_add_line(void);
int							arrow_up(void);
int							arrow_down(void);
int							check_key(int func(char key[BUFF_SIZE_READ + 1]));
int							event_key(char b[BUFF_SIZE_READ + 1]);*/

#endif
