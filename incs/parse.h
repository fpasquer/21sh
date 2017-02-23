/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:54:26 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/23 13:29:29 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/*
**	numero operateur :
**	1 = ;
**	2 = &&
**	3 = pipe
**	4 = ||
**	cmd = type de redirection :
**	2 = <
**	3 = <<
**	4 = >
**	5 = >>
*/

# define PV 1
# define ET 2
# define PIP 3
# define OU 4

# define DROITE 2
# define D_DROITE 3
# define GAUCHE 4
# define D_GAUCHE 5

# define MSG_ERR(hist, val, ret) hist.type_error = val;return (ret)

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

typedef struct		s_options_hist
{
	int				i;
	int				(*f)(int);
}					t_options_hist;

int					option_none(int offset);
int					option_clear(int offset);
int					option_append(int offset);
int					option_nappend(int offset);
int					option_delete(int offset);

typedef struct		s_hist
{
	int				flags;
	int				offset;
	int				i;
	int				type_error;
}					t_hist;

t_options_hist		g_options_hist[5];

typedef struct			s_cmd
{
	int					cmd;
	int					op;
	int					fd;
	int					tgt_fd;
	int					done;
	char				*line;
	char				**arg;
	struct s_env		*env;
	struct s_cmd		*left;
	struct s_cmd		*right;
}						t_cmd;

/*
**	cmd : numero de l'operateur de redirection
**	op : numero de l'operateur de separation
**	fd : filedes du fichier une fois cree/ouvert
**	tgt_fd : filedes cible de notre redirection
**	done : retour de l'execution de la cmd
**	line : ligne de cmd des maillon pere emputer des redirections si il y en a
**	arg : splite de line original pour chaque ligne redirection comprise
**	left : acces au sous maillon de redirection s'il y en as
**	right : acces a la ligne de cmd suivante si elle existe
*/

/*
**	parse.c
*/

t_cmd					*parse_cmd(char *line, t_cmd *cmd, int i);
void					free_cmd(t_cmd *cmd);

/*
**	parse2.c
*/

int						parse_cmd2(t_cmd *cmd, int i);
t_cmd					*exit_parse(t_cmd *cmd, char *str);

/*
**	quotes.c
*/

void					scop(char *line, int *i, int *size);
void					tacke_more_arg(t_cmd *cmd, t_cmd *red);

#endif
