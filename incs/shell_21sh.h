/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:58:42 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/09 14:10:58 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_21SH_H

# define SHELL_21SH_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>
# include "../libft/libft.h"

# define ERROR -1
# define LEN_PATH_MAX 200
# define SIZE_HASH 300
# define NAME_SHELL "xterm-256color"

/*
**	name :			nom de la variable env
**	value :			valeur de la variable env
*/
typedef struct				s_env
{
	char					*name;
	char					*value;
	int						index;
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
}							t_21sh;

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
int							del_env(void);

/*
**	builtin_env.c
*/
int							get_tab_env(char *l_cmd, char ***tab);

/*
**	options_env.c
*/
int							tab_env_i(char *l_cmd, char ***tab);
int							tab_env_u(char *l_cmd, char ***tab);
int							tab_env(char *l_cmd, char ***tab);

/*
**	Supprimer
*/
int							print_all_bin(void);
int							print_all_env(void);

#endif
