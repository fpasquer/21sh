/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 08:58:42 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/08 16:59:19 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_21SH

# define SHELL_21SH

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <termios.h>
# include "../libft/libft.h"

# define ERROR -1
# define LEN_PATH_MAX 200

/*
**	term_name :		nom du terminal recu dans **env
**	home :			path du home dans la variable env
**	pwd :			path actuel
**	old_pwd :		pwd precedent
**	sh_lvl :		niveau de profondeur du shell
**	user :			nom de session de l'utilisateur
**	path			path sur une ligne
**	tab_path		path split sur :
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
	unsigned int			sh_lvl;
}							t_21sh;

/*
**	init_21sh.c
*/
t_21sh						*init_21sh(void);
t_21sh						*get_21sh(t_21sh *shell_21sh);
int							del_21sh(void);

/*
** fonctions.c
*/
int							save_pwd(char **dest);
int							save_path(t_21sh **sh, char *path);

/*
** bin.c
*/
int							save_bin(t_21sh *sh);
int							del_bin(void);
#endif
