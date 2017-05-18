/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:54:26 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/18 14:59:25 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>

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

# define GAUCHE 2
# define D_GAUCHE 3
# define DROITE 4
# define D_DROITE 5

typedef struct			s_cmd
{
	pid_t				pid;
	int					status;
	int					cmd;
	int					op;
	int					fd;
	int					tgt_fd;
	int					done;
	char				*line;
	char				**arg;
	int					env_i;
	struct s_env		*env;
	struct s_cmd		*left;
	struct s_cmd		*right;
}						t_cmd;

/*
**	pid : numero du procecusse dans lequelle la cmd est execute
**	status : status du procecusse pid
**	cmd : numero de l'operateur de redirection
**	op : numero de l'operateur de separation
**	fd : filedes du fichier de redirection une fois cree/ouvert
**	tgt_fd : filedes cible de notre redirection
**	done : retour de l'execution de la cmd
**	line : ligne de cmd des maillon pere emputer des redirections si il y en a
**	arg : splite de line original pour chaque ligne redirection comprise
**	env_i : est different de 0 si la cmd est exeecuter dans un environement vide
**	env : est non NULL si la cmd est executer par le builtin env
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
int						tk_fd(char *line, int size);

#endif
