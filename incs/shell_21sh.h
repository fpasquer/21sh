/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:58:42 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/11 16:08:04 by fpasquer         ###   ########.fr       */
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
# define NAME_SHELL "xterm-256color"
# define SIZE_PROMT 2000

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
	size_t					len_name;
	struct stat				stat;
	struct s_bin			*next;
}							t_bin;

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
	int						nb_var_env;
	t_bin					*hash[SIZE_HASH];
	t_env					*env;
	struct termios			reset;
	struct termios			term_param;
	struct winsize			win;
}							t_21sh;

/*
**
**	str 			: chaine entiere envoye par l'utilisateur
**	bin 			: nom de l'executable
**	bin_argv		: tableau contenant l'executable et les parametres
**	bin_param		: tableau contenant uniquement les parametres
**	bin_argc		: contient le nombre de parametre + l'executable
**
*/

typedef struct 				s_stin_content
{
	char 					*str;
	char 					*bin;
	char 					**bin_argv;
	char 					**bin_param;
	int 					bin_argc;
}							t_stin_content;

/*
**
** Tableau sur pointeur sur fonction permettant de verifier si le binaire
** entree est un builtin
**
*/

typedef struct 				s_builtin_lst
{
	char 					*str;
	int 					(*p)(t_stin_content *stin);
}							t_builtin_lst;

void						builtin_or_not(t_stin_content *content);

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

/*
**	sort_fonctions.c
*/
int							len_tri(void *node1, void *node2);

/*
**	sort_list.c
*/
void						sort_list(t_bin **liste,
				int (fonc_tri)(void *, void *));

/*
**	env.c
*/

int							save_env(t_env **env);
int							add_env(t_env **env, char *str, int index, bool ad);
int							del_list_env(t_env **list);
int							del_env(void);

/*
**	builtin_env.c
*/
int							builtin_env(t_stin_content *contentst);

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

/*
**	term.c
*/
int							init_term(t_21sh **sh);

/*
**	functions_key.c
*/
void						key_exit(int val_exit);

/*
**	Supprimer
*/
int							print_all_bin(void);
int							print_all_env(void);

/*
**		fonction temporaire. 
*/

t_stin_content				parse_stin(char *line); 

/*
** BUILTIN
*/

int	 						cd(t_stin_content *cmd);

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

#endif
