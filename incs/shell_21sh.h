/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_21sh.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:18:30 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/26 18:07:44 by fcapocci         ###   ########.fr       */
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
# define SELECTED_COLOR "\033[0;7m"
# define SPACE_CHAR 32

# define NONE 0
# define CLEAR 1
# define APPEND 2
# define NAPPEND 4
# define DELETE 8

# define FUNC_NONE 0
# define FUNC_CLEAR 1
# define FUNC_APPEND 2
# define FUNC_NAPPEND 3
# define FUNC_DELETE 4

# define WRONG_BUILTIN 1
# define ERROR_INCONNU 2
# define ERROR_PARAM 3
# define ERROR_OFFSET 4
# define WRONG_OFFSET 5

# define ENV_CREAT 21

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
	size_t					y;
	size_t					len;
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
	char					*cpy_tmp;
	int						last_exe;
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
**	Tableau sur pointeur sur fonction permettant de verifier si le binaire
**	entree est un builtin
*/

/*
**	builtin_or_not.c
*/
typedef struct				s_builtin_lst
{
	char					*str;
	int						(*p)(t_cmd *stin);
}							t_builtin_lst;

int							builtin_pipe(t_cmd *content, int i, int std[3]);
int							builtin_or_not(t_cmd *content, int i, int std[3]);

/*
**	init_21sh.c
*/
t_21sh						*init_21sh(void);

/*
**	get_and_del_21sh.c
*/
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
int							add_env_(char *name, char *value);
int							del_list_env(t_env **list);
int							del_env(void);

/*
**	builtin_env.c
*/
char						get_flags_env(char **l_cmd, t_env *sb);
int							error_env(char flags, char *l_cmd);
int							builtin_env(t_cmd *contentst);

/*
**	options_env.c
*/
int							moove_l_cmd(char **l_cmd);
t_env						*get_at_add(char **list_env);
char						**get_new_tab(t_env *lst_1, t_env *lst_2);

/*
**	options_env2.c
*/
int							tab_env_i(char **l_cmd, char ***tab);
int							tab_env_u(char **l_cmd, char ***tab, t_cmd *cntt);
int							tab_env(char **l_cmd, char ***tab, t_cmd *content);
int							print_env(char **tab);

/*
**	options_env3.c
*/
int							take_cmd_if_exist(char **tmp_line, char ***tab,
				t_cmd *content, int choice);
int							check_if_env_creat_cmd(t_cmd *c);

/*
**	builtin_echo.c
*/
int							builtin_echo(t_cmd *cmd);

/*
**	loop_shell.c
*/
void						loop_shell(void);

/*
**	print_prompt.c
*/
int							print_prompt(void);
int							clean_and_put_prompt(void);

/*
**	term.c
*/
int							init_term(t_21sh **sh);
int							my_out_put(int c);
int							put_cmd_term(char *cmd);

/*
**	print_history.c
*/
int							print_history(void);

/*
**	search_history.c
*/
int							search_history(void);

/*
**	del_history.c
*/
int							del_hist(void);

/*
**	init_history.c
*/
int							init_history(void);
int							add_history(t_history **hist, char *line);

/*
**	print_event.c
*/
char						*put_words_event(t_list_print *lst, int len,
		int nb_word_line);
void						print_g_line(void);

/*
**	print_list_term.c
*/
char						*print_list_term(t_21sh *sh, char **list,
		bool select);

/*
**	autocompletion.c
*/
int							autocompletion(void);
int							add_word_to_g_line(char **ret, char *begin);
int							del_car_begin_in_g_line(size_t len);

/*
**	functions_signaux.c
*/
void						resize_win(int val);
void						ctrl_d(int val);
void						sig_manager(void);

/*
**	BUILTIN
*/
int							cd(t_cmd *cmd);
int							builtin_setenv(t_cmd *cmd);
int							builtin_unsetenv(t_cmd *content);
int							builtin_exit(t_cmd *cmd);

typedef struct				s_hist
{
	char					*line;
	int						flags;
	int						offset;
	int						i;
	int						type_error;
}							t_hist;

/*
**	builtin_history.c
*/
int							builtin_history(t_cmd *cmd);

/*
**	options_history.c
*/
int							option_none(t_hist hist);
int							option_clear(t_hist hist);
int							option_append(t_hist hist);
int							option_delete(t_hist hist);

/*
**	options_history2.c
*/
typedef struct				s_options_hist
{
	int						i;
	int						(*f)(t_hist);
}							t_options_hist;

t_hist						msg_err(t_hist *hist, int val, t_hist *ret);
int							option_nappend(t_hist hist);
int							exe_hist(t_hist hist);

/*
**	Renvoi la valeur de l'environnement.
*/
char						*getenv_value(char *name);

/*
**	Change la valeur de l'environnement.
*/
int							modify_env_value(char *name, char *value);

/*
**	Verifie sur l'env existe
*/
int							check_if_env_exist(char *name, t_env *sub_env);

/*
**	Permet de recuperer l'environnement en array.
*/
char						**l_l_to_arr_env(t_env *cmd_env, int env_i);
void						ft_print_env_array(char **env);
int							delete_env_array(char **env);

/*
**	split_quotes.c
*/
char						**split_quotes(char *str);

/*
**	fd_manager.c
*/
void						change_pipe(int pipfd[2], int save_fd, int choice);
void						save_fd(int std[3]);
void						reset_fd(int std[3]);
int							redirection_fd_manage(int redirect_fd, int tgt_fd);

/*
**	exe_binaire.c
**	Fonction execute les binaires
*/
void						exe_binaire(t_cmd *cmd);

/*
**	exe_binaire2.c
**	Fonction execute les binaires
*/
void						ft_execve(t_cmd *cmd, char **env, char *exe);

/*
**	redirection.c
**	check le redirections et renvoie vers des fonctions aproprie
*/
typedef struct				s_redirect_selec
{
	int						num;
	int						(*p)(t_cmd *redirect, int tgt_fd);
}							t_redirect_selec;

int							redirecting(t_cmd *redirect, int index, int tgt_fd,
							int i);

/*
**	redirection2
**	fonctions effectuant la redirection voulu
*/
int							read_funct(t_cmd *redeirect, int tgt_fd);
int							put_heredoc(t_cmd *redeirect, int tgt_fd);
int							write_funct(t_cmd *redeirect, int tgt_fd);
int							d_write_funct(t_cmd *redeirect, int tgt_fd);

/*
**	heredoc.c
*/
int							heredoc(char *token, char **buff);

#endif
