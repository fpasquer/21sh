#ifndef PARSE_H
# define PARSE_H

// # include "shell_21sh.h"

/*
**  numero operateur :
**	1 = ;
** 	2 = &&
** 	3 = ||
**
**	cmd = type de redirection :
**	1 = pipe
** 	2 = <
**	3 = <<
**	4 = >
**	5 = >>
**
*/

# define PV 1
# define ET 2
# define OU 3

# define BARRE 1
# define DROITE 2
# define D_DROITE 3
# define GAUCHE 4
# define D_GAUCHE 5

typedef struct			s_cmd
{
	int					cmd;
	int					op;
	int					argc;
	int					fd;
	int					tgt_fd;
	int					done;
	char				*line; // UNIQUEMENT LA COMMANDE
	char				**arg;
	struct s_cmd		*left;
	struct s_cmd		*right;
}						t_cmd;

/*
**	cmd : numero de l'operateur de redirection
**	op : numero de l'operateur de separation
**	fd : files descriptor utilise (1 par defaut)
**	done : reussite de l'execution de la cmd
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

void					print_cmd(t_cmd *cmd); // debug

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
