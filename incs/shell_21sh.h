/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:58:42 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/19 18:22:33 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_21SH_H

# define SHELL_21SH_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include <sys/ioctl.h>

# include <sys/stat.h>
# include <sys/types.h>

# include "../libft/libft.h"
# include "parse.h"

FILE *debug;

# define ERROR -1
# define LEN_PATH_MAX 200
# define SIZE_HASH 300
# define SIZE_DICO 27
# define NAME_SHELL "xterm-256color"
# define SIZE_PROMT 2000

# define HISTORY "/tmp/history.txt"

# define COLOR_POMT "\033[032;1m"
# define RESET_COLOR "\033[0m"
# define COLOR_LINE "\033[034;1;4m"
# define SPACE_CHAR 32

typedef struct stat			t_stat;

/*
**	name :			nom de la variable env
**	value :			valeur de la variable env
**	index :			position dans la liste chainee
**	add :			pour recreer le tab 2d env
*/
typedef struct				s_env
{
	char					*name;
	char					*value;
	int						index;
	bool					add;
	struct s_env			*next;
}							t_env;

/*
**	name :			nom du binaire
**	path :			path du binaire
**	path_name :		path + nom du binaire
**	i_hash :		position dans la table de hash
**	len_name :		len de name
**	stat :			retour de lstat sur le binaire
**	next :			adresse du maillon suivant
*/

typedef struct				s_bin
{
	char					*name;
	char					*path;
	char					*path_name;
	unsigned int			i_hash;
	unsigned int			i_sort;
	size_t					len_name;
	struct stat				stat;
	struct s_bin			*next;
	struct s_bin			*n_dico;
}							t_bin;

/*
**	line :			ligne de l'historique
**	next :			pointeur sur le maillon suivant
*/
typedef struct				s_history
{
	char					*line;
	struct s_history		*curs;
	struct s_history		*next;
	struct s_history		*prev;
}							t_history;

/*
**	word :					mot a afficher
**	len :					longueur de word
**	next :					pointeur sur le maillon suivant
**	prev :					pointeur sur le millon precedent;
*/
typedef struct				s_print_list
{
	char					*word;
	size_t					len;
	struct s_print_list		*curs;
	struct s_print_list		*next;
	struct s_print_list		*prev;
}							t_list_print;

/*
**	term_name :		nom du terminal recu dans **env
**	home :			path du home dans la variable env
**	pwd :			path actuel
**	old_pwd :		pwd precedent
**	sh_lvl :		niveau de profondeur du shell
**	user :			nom de session de l'utilisateur
**	path :			path sur une ligne
**	tab_path :		path split sur :
**	hash :			table de hash des binaire
**	env :			liste des variables d'env
**	reset :			structure pour reset les parametres du term
**	term_param :	structure pour save les parametres du term
**	hist :			pointeur sur le premier maillon de l'historique
**	pos :			decalage entre le prompt et le curseur en y
**	pos_prev :		old decalage entre le prompt et le curseur en y
*/

typedef struct				s_21sh
{
	char					*term_name;
	char					*home;
	char					*pwd;
	char					*old_pwd;
	char					*user;
	char					*path;
	char					**tab_path;
	int						sh_lvl;
	int						pos;
	int						pos_prev;
	int						nb_var_env;
	size_t					len_prompt;
	t_bin					*hash[SIZE_HASH];
	t_bin					*dico[SIZE_DICO];
	t_env					*env;
	t_history				*hist;
	struct termios			reset;
	struct termios			term_param;
	struct winsize			win;
}							t_21sh;


/*
**
** Tableau sur pointeur sur fonction permettant de verifier si le binaire
** entree est un builtin
**
*/

typedef struct 				s_builtin_lst
{
	char 					*str;
	int 					(*p)(t_cmd *stin);
}							t_builtin_lst;

void						builtin_or_not(t_cmd *content);

/*
**	init_21sh.c
*/
t_21sh						*init_21sh(void);
t_21sh						*get_21sh(t_21sh *shell_21sh);
int							del_21sh(void);

/*
**	fonctions.c
*/
int							save_pwd(char **dest);
int							save_path(t_21sh **sh, char *path);
int							nb_match_var_env(char **tab);

/*
**	bin.c
*/
int							save_bin(t_21sh *sh);
int							del_bin(void);

/*
**	table_hash.c
*/
int							i_table_hash(char *name, int size_hash);
int							get_path_bin(char *name_bin, char **path_name);

/*
**	sort_fonctions.c
*/
int							len_tri(void *node1, void *node2);
int							name_tri(void *node1, void *node2);

/*
**	sort_list.c
*/
void						sort_list(t_bin **liste,
				int (fonc_tri)(void *, void *));

/*
**	dico.c
*/
int							save_dico(t_bin **n);


/*
**	env.c
*/

int							save_env(t_env **env);
int							add_env(t_env **env, char *str, int index, bool ad);
int 						add_env_(char *name, char *value);
int							del_list_env(t_env **list);
int							del_env(void);

/*
**	builtin_env.c
*/
int							builtin_env(t_cmd *contentst);

/*
**	options_env.c
*/
int							tab_env_i(char **l_cmd, char ***tab);
int							tab_env_u(char **l_cmd, char ***tab);
int							tab_env(char **l_cmd, char ***tab);

/*
**	loop_shell.c
*/
void						loop_shell(void);
int							print_prompt(void);
int							exe_cmd(t_history **hist, char **line);

/*
**	list_bin.c
*/
int							list_all_bin(char *path, char *begin_name);

/*
**	term.c
*/
int							init_term(t_21sh **sh);

/*
**	functions_key.c
*/
void						key_exit(unsigned char val_exit);
int							key_del_hist(void);
int							print_history_up(void);
int							print_history_down(void);
int							mouve_righ(void);
int							mouve_left(void);
int							del_right(void);
int							autocompletion(void);

/*
**	history.c
*/
int							init_history(void);
int							del_hist(void);
int							add_history(t_history **hist, char **line);
int							print_history(void);
//int							add_to_g_lines(char *line);

/*
**	print_event.c
*/
char						*put_words_event(t_list_print *lst, int  len,
		int nb_word_line,t_21sh  *sh);
int							put_cmd_term(char *cmd);
void						print_g_line(void);

/*
**	autocompletion.c
*/
int							put_pompt_word(char **word);

/*
**	print_list_term.c
*/
char						*print_list_term(t_21sh *sh, char **list,
		bool select);

/*
**	functions_signaux.c
*/
void						resize_win(int val);
void						ctrl_d(int val);

/*
**	Supprimer
*/
int							print_all_bin(void);
int							print_all_env(void);
void						print_dico(void);

/*
**		fonction temporaire. 
*/

// t_stin_content				parse_stin(char *line); 

/*
** BUILTIN
*/

int	 						cd(t_cmd *cmd);
int 						builtin_setenv(t_cmd *cmd);
int							builtin_exit(t_cmd *cmd);

/*
** Renvoi la valeur de l'environnement.
*/

char						*getenv_value(char *name);

/*
** Change la valeur de l'environnement.
*/

int 						modify_env_value(char *name, char *value);

/*
** Verifie sur l'env existe
*/

int							check_if_env_exist(char *name);


/*
** Permet de recuperer l'environnement en array.
*/

int							c_l_to_arr_env(char ***tab);

#endif
