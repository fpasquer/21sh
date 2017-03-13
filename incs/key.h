/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:17:49 by fcapocci          #+#    #+#             */
/*   Updated: 2017/03/13 22:58:59 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H

# define KEY_H

# include "shell_21sh.h"

# define MAX_LEN_LINE 10
# define SIZE_BUFF 8
# define SIZE_MEM 2000

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
}							t_line;

t_line						*g_lines;
t_line						*g_curs;
size_t						g_y;
size_t						g_x;

# define DS					(b[0] == -62 && b[1] == -89 && b[2] ==  83 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //§ au dessus de tab
# define PLUS_MINUS			(b[0] == -62 && b[1] == -79 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //±

# define TAB				(b[0] ==   9 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //tabulation
# define ENTER				(b[0] ==  10 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //\n
# define ESC				(b[0] ==  27 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //echap

# define F1					(b[0] ==  27 && b[1] ==  79 && b[2] ==  80 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //f1
# define F2					(b[0] ==  27 && b[1] ==  79 && b[2] ==  81 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //f2
# define F3					(b[0] ==  27 && b[1] ==  79 && b[2] ==  82 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //f3
# define F4					(b[0] ==  27 && b[1] ==  79 && b[2] ==  83 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //f4
# define F5					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  53 && b[4] == 126 && b[5] ==   0) //f5
# define F6					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  55 && b[4] == 126 && b[5] ==   0) //f6
# define F7					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  56 && b[4] == 126 && b[5] ==   0) //f7
# define F8					(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  57 && b[4] == 126 && b[5] ==   0) //f8
# define F13				(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  59 && b[4] ==  50 && b[5] ==  80) //13
# define F14				(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  59 && b[4] ==  50 && b[5] ==  81) //f14
# define F15				(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  59 && b[4] ==  50 && b[5] ==  82) //f15
# define F9					(b[0] ==  27 && b[1] ==  91 && b[2] ==  50 && b[3] ==  48 && b[4] == 126 && b[5] ==   0) //f9
# define F10				(b[0] ==  27 && b[1] ==  91 && b[2] ==  50 && b[3] ==  49 && b[4] == 126 && b[5] ==   0) //f10
//# define F11
//# define F12

# define ARROW_UP			(b[0] ==  27 && b[1] ==  91 && b[2] ==  65 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //fleche haut
# define ARROW_DOWN			(b[0] ==  27 && b[1] ==  91 && b[2] ==  66 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //fleche bas
# define ARROW_RIGHT		(b[0] ==  27 && b[1] ==  91 && b[2] ==  67 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //fleche droite
# define ARROW_LEFT			(b[0] ==  27 && b[1] ==  91 && b[2] ==  68 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //fleche gauche
# define HOME				(b[0] ==  27 && b[1] ==  91 && b[2] ==  72 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //home
# define END				(b[0] ==  27 && b[1] ==  91 && b[2] ==  70 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //end
# define SHIFT_UP			(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  59 && b[4] ==  50 && b[5] ==  65) //shift flech haut
# define SHIFT_DOWN			(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  59 && b[4] ==  50 && b[5] ==  66) //shift flech bas
# define SHIFT_LEFT			(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  59 && b[4] ==  50 && b[5] ==  68) //shift flech gauche
# define SHIFT_RIGHT		(b[0] ==  27 && b[1] ==  91 && b[2] ==  49 && b[3] ==  59 && b[4] ==  50 && b[5] ==  67) //shift flech haut
# define SEL_MOD			(b[0] ==  20 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //ctrl_t
# define CPY				(b[0] ==  12 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //ctrl_l
# define CUT				(b[0] ==  21 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //ctrl_u
# define PAST				(b[0] ==  16 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //ctrl_p

# define SPACE				(b[0] ==  32 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //' '
# define EXCLAM_MACK		(b[0] ==  33 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //!
# define INVERTED_COMMA		(b[0] ==  34 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //"
# define SHARP				(b[0] ==  35 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //#
# define DOLLAR				(b[0] ==  36 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //$
# define PERCENT			(b[0] ==  37 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //%
# define AND				(b[0] ==  38 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //&
# define APOSTROPHE			(b[0] ==  39 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //'
# define BRACKET_OPEN		(b[0] ==  40 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //(
# define BRACKET_CLOSE		(b[0] ==  41 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //)
# define STAR				(b[0] ==  42 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //*
# define PLUS				(b[0] ==  43 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //+
# define COMMA				(b[0] ==  44 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //,
# define CM					(b[0] ==  45 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //- clavier
# define POINT				(b[0] ==  46 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //.
# define SLACH				(b[0] ==  47 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) ///
# define C0					(b[0] ==  48 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //0 clavier
# define C1					(b[0] ==  49 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //1 clavier
# define C2					(b[0] ==  50 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //2 clavier
# define C3					(b[0] ==  51 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //3 clavier
# define C4					(b[0] ==  52 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //4 clavier
# define C5					(b[0] ==  53 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //5 clavier
# define C6					(b[0] ==  54 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //6 clavier
# define C7					(b[0] ==  55 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //7 clavier
# define C8					(b[0] ==  56 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //8 clavier
# define C9					(b[0] ==  57 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //9 clavier
# define TWO_POINTS			(b[0] ==  58 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //:
# define SEMICOLUM			(b[0] ==  59 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //;
# define LEFT				(b[0] ==  60 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //<
# define EGA				(b[0] ==  61 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //= clavier
# define RIGHT				(b[0] ==  62 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //>
# define QUESTION_MACK		(b[0] ==  63 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //?
# define AT					(b[0] ==  64 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //@
# define HA					(b[0] ==  65 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //A
# define HB					(b[0] ==  66 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //B
# define HC					(b[0] ==  67 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //C
# define HD					(b[0] ==  68 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //D
# define HE					(b[0] ==  69 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //E
# define HF					(b[0] ==  70 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //F
# define HG					(b[0] ==  71 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //G
# define HH					(b[0] ==  72 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //H
# define HI					(b[0] ==  73 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //I
# define HJ					(b[0] ==  74 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //J
# define HK					(b[0] ==  75 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //K
# define HL					(b[0] ==  76 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //L
# define HM					(b[0] ==  77 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //M
# define HN					(b[0] ==  78 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //N
# define HO					(b[0] ==  79 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //O
# define HP					(b[0] ==  80 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //P
# define HQ					(b[0] ==  81 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //Q
# define HR					(b[0] ==  82 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //R
# define HS					(b[0] ==  83 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //S
# define HT					(b[0] ==  84 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //T
# define HU					(b[0] ==  85 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //U
# define HV					(b[0] ==  86 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //V
# define HW					(b[0] ==  87 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //W
# define HX					(b[0] ==  88 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //X
# define HY					(b[0] ==  89 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //Y
# define HZ					(b[0] ==  90 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //Z
# define HOOK_OPEN			(b[0] ==  91 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //[
# define BACKSLACH			(b[0] ==  92 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //'\'
# define HOOK_CLOSE			(b[0] ==  93 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //]
# define CIRCONFLEX			(b[0] ==  94 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //^
# define UNDERSCORE			(b[0] ==  95 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //_
# define GRAVE_ACCENT		(b[0] ==  96 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //`
# define LA					(b[0] ==  97 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //a
# define LB					(b[0] ==  98 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //b
# define LC					(b[0] ==  99 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //c
# define LD					(b[0] == 100 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //d
# define LE					(b[0] == 101 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //e
# define LF					(b[0] == 102 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //f
# define LG					(b[0] == 103 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //g
# define LH					(b[0] == 104 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //h
# define LI					(b[0] == 105 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //i
# define LJ					(b[0] == 106 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //j
# define LK					(b[0] == 107 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //k
# define LL					(b[0] == 108 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //l
# define LM					(b[0] == 109 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //m
# define LN					(b[0] == 110 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //n
# define LO					(b[0] == 111 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //o
# define LP					(b[0] == 112 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //p
# define LQ					(b[0] == 113 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //q
# define LR					(b[0] == 114 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //r
# define LS					(b[0] == 115 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //s
# define LT					(b[0] == 116 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //t
# define LU					(b[0] == 117 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //u
# define LV					(b[0] == 118 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //v
# define LW					(b[0] == 119 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //w
# define LX					(b[0] == 120 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //x
# define LY					(b[0] == 121 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //y
# define LZ					(b[0] == 122 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //z
# define BRASE_OPEN			(b[0] == 123 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //{
# define PIPE				(b[0] == 124 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //|
# define BRASE_CLOSE		(b[0] == 125 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //}
# define TILD				(b[0] == 126 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //~
# define DEL				(b[0] == 127 && b[1] ==   0 && b[2] ==   0 && b[3] ==   0 && b[4] ==   0 && b[5] ==   0) //<- del gauche
# define DEL_R				(b[0] ==  27 && b[1] ==  91 && b[2] ==  51 && b[3] == 126 && b[4] ==   0 && b[5] ==   0) //-> del droite

char						*get_line_entree(void);
int							add_c_to_line(char c, t_line **lines);
int							insert_word_in_g_line(char *word, t_line **line);
char						*make_tab(void);
void						del_g_lines(void);
int							change_value_g_curs_line(char *word);

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

int							get_y_x_line(char *line, unsigned int *y,
		unsigned int *x);
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
#endif
