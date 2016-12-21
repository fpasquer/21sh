/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 19:27:10 by fpasquer          #+#    #+#             */
/*   Updated: 2016/12/21 16:06:39 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#include <limits.h>

#define KEY_IGNORE -2
#define NONE 0
#define D_QUOTE '\"'
#define QUOTE '\''
#define PRINT_MAX 500
#define CC curs->curs

static char					cmd_keyboard(char b[SIZE_BUFF])
/*
**	check si la touche utilise est un event ou un caractere
*/
{
	if (ESC)
		key_exit(EXIT_SUCCESS);
	else if (F1)
		key_del_hist();
	/*else if (F2)
		print_history();*/
	/*else if (TAB)
		autocompletion();*/
	else if (ARROW_UP)
		print_history_up();
	else if (ARROW_DOWN)
		;//print_history_down();
	else if (ARROW_RIGHT)
		move_right();
	else if (ARROW_LEFT)
		move_left();
	else if (DEL)
		del_left();
	else if ((b[0] >= 32 && b[0] <= 126) || ENTER)
		return (b[0]);
	return (KEY_IGNORE);
}

static char					get_char_keyboard(void)
/*
**	recupere la touche presse
*/
{
	char					b[SIZE_BUFF];

	ft_bzero(b, sizeof(b));
	if (read(STDIN_FILENO, b, SIZE_BUFF) <= 0)
		return (ERROR);
	return (cmd_keyboard(b));
}

static int					is_end(char c)
/*
**	regarde si c'est la fin de ligne en fonction les quotes simple ou double
*/
{
	int						quote;
	t_entry					*curent_c;
	t_line					*curs;

	if (c != '\n')
		return (false);
	if ((curs = g_lines) == NULL)
		return (ERROR);
	g_lines->count_line++;
	quote = NONE;
	while (curs != NULL)
	{
		curent_c = curs->line;
		while (curent_c != NULL)
		{
			if (curent_c->c == '\'' && (quote == NONE || quote == QUOTE))
				quote = (quote == NONE) ? QUOTE : NONE;
			if (curent_c->c == '\"' && (quote == NONE || quote == D_QUOTE))
				quote = (quote == NONE) ? D_QUOTE : NONE;
			curent_c = curent_c->next;
		}
		curs = curs->next;
	}
	return ((quote == NONE) ? true : false);
}

static int					loop_place_curs(size_t y, size_t x)
/*
**	boucles qui replace le curseur au debut du prompt suite a l'ajout d'un caractere
*/
{
	//getchar();
	while (y-- > 1)
		if (put_cmd_term("up") == ERROR)
			return (ERROR);
	while (x-- + 1 > 0)
	{
		//fprintf(debug, "le replace x = %3zu\n", x + 1);
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	}
	//getchar();
	return (true);
}

char						last_c(t_line *line, size_t i)
/*
**	POur debug. Fonction qui recupere le dernier caractere entre au clavier Peut etre supprimee
*/
{
	size_t					loop;
	t_entry					*curs;

	if (line != NULL && line->line != NULL)
	{
		curs = line->line;
		loop = 0;
		while (curs != NULL)
		{
			if (loop++ == i)
				return (curs->c);
			curs = curs->next;
		}
	}
	return ('0');
}

static int					check_if_g_curs_c_is_enter(void)
/*
**	regarde si le caractere ou le cuseur de la ligne ce trouve est un \n pour retourner au debut de la ligne du dessus
*/
{
	size_t					loop;

	if (g_curs == NULL)
		return (ERROR);
	if (g_curs->curs != NULL && g_curs->curs->c == '\n')
	{
		if (put_cmd_term("up") == ERROR)
			return (ERROR);
		loop = 0;
		while (loop++ < g_curs->curs->x_i)
			if (put_cmd_term("nd") == ERROR)
				return (ERROR);
	}
	return (true);
}

static int					save_y_i(size_t *y, size_t *x)
/*
**	pour savoir le deplacement a faire pour placer le curseur au debut du promt
*/
{
	size_t					loop;
	t_line					*curs;
	t_21sh					*sh;

	sh = get_21sh(NULL);
	if (sh == NULL || (curs = g_lines) == NULL || y == NULL || x == NULL)
		return (ERROR);
	loop = 0;
	(*x) = sh->len_prompt;
	(*y) = 0;
	if (curs->x_i == 0 && curs->y_i == 0)
		return (true);
	while (curs != NULL)
	{
		loop = loop + 1;
		(*y) += curs->y_i;
		//fprintf(debug, "(*x) = %3zu (*y) = %3zu\n", (*x), (*y));
		(*x) = curs->x_i + 1;
		//fprintf(debug, "(*x) = %3zu (*y) = %3zu\n", (*x), (*y));
		curs = curs->next;
	}
	(*y) += loop;
	return (check_if_g_curs_c_is_enter());
}

int							place_curs(void)
/*
**	repalce le curseur au debut du promt
*/
{
	size_t					x_i;
	size_t					y_i;

	if (save_y_i(&y_i, &x_i) == ERROR)
		return (ERROR);
	return (loop_place_curs(y_i, x_i));
}

static int						clean_and_put_prompt(void)
/*
**	efface l'ensemble des caracteres qui ce trouve apres le curseur et ecrit le promt
*/
{
	int							ret;

	ret = put_cmd_term("cd");
	print_prompt();
	return (ret);
}

/*static int					replace_i(void)
 *	Replace mal le curseur si la ligne a des entrees
{
	size_t					i;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs = curs->next;
	i = curs->i;
	while (i++ + 1< curs->len)
		if (put_cmd_term("le") == ERROR)
			return (ERROR);
	return (true);
}*/

static int					move_enter_line_1(void)
/*
 *	petite variande de mouve_entre a cause du decalage du promt
*/
{
	size_t					i;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	i = 0;
	while (i++ < sh->len_prompt)
	{
		//fprintf(debug, "nd line 1\n");
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
	}
	return (true);
}

static int					move_enter(t_entry *curs)
/*
**	
*/
{
	size_t					i;
	size_t					y;
	t_entry					*tmp;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if ((tmp = curs->prev) == NULL)
		return (true);
	i = 0;
	//fprintf(debug, "y = %3zu x = %3zu c = %c\n", y, tmp->x_i, tmp->c);
	if ((y = tmp->y_i) == tmp->y_i && tmp->x_i > 0)
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
	while (tmp != NULL && tmp->c != '\n' && tmp->x_i > 0)
	{
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
		//fprintf(debug, "c = %c x = %3zu y = %3zu", tmp->c, tmp->x_i, tmp->y_i);
		tmp = tmp->prev;
		fprintf(debug, "nd i = %3zu\n", ++i);
	}
	if (g_curs == g_lines && y == 0 && (i = 0) == 0)
		while (i++ < sh->len_prompt)
		{
			if (put_cmd_term("nd") == ERROR)
				return (ERROR);
			fprintf(debug, "nd line 1 i %3zu\n", i);
		}
	if (put_cmd_term("up") == ERROR)
		return (ERROR);
	//fprintf(debug, "up\n");
	return (true);
}

static int					replace_i(unsigned int ntr)
/*
**	replace le curseur juste apres le caratere qui vient detre ajoute
*/
{
	int						ret;
	size_t					i;
	t_entry					*curs;

	if (g_curs == NULL || (curs = g_curs->curs) == NULL)
		return (g_curs == NULL ? ERROR : true);
	while (curs->next != NULL)
		curs = curs->next;
	i = 0;
	//getchar();
	while (g_curs->i + i < g_curs->len - 1 && curs != NULL)
	{
		if (curs->c == '\n')
			ret = move_enter(curs);
		else
		{
			//	fprintf(debug, "c = %c x = %3zu y = %3zu", curs->c, curs->x_i, curs->y_i);
			fprintf(debug, "le\n");
			ret = put_cmd_term("le");
		}
		if (ret == ERROR)
			return (ERROR);
		curs = curs->prev;
		i++;
	}
	while (ntr-- + 1 > 1)
	{
		fprintf(debug, "nd enter\n");
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
	}
	//fprintf(debug, "\n\n");
	//getchar();
	return (true);
}

int							put_cmd(void)
/*
**	parcour toute les lignes pour afficher l'ensemble des caracteres
*/
{
	char					buff[PRINT_MAX + 1];
	unsigned int			i;
	unsigned int			ntr;
	t_line					*curs;
	t_entry					*c_line;

	if (clean_and_put_prompt() != true || (curs = g_lines) == NULL)
		return (ERROR);
	ntr = 0;
	while (curs != NULL)
	{
		c_line = curs->line;
		while (c_line != NULL && (i = 0) == 0)
		{
			ft_bzero(buff, sizeof(buff));
			while (c_line != NULL && i < PRINT_MAX - 1)
			{
				buff[i++] = c_line->c;
				ntr = (c_line->c == '\n' && c_line->x_i == 0 && c_line->prev != NULL && c_line->prev->c != '\n') ? ntr + 1 : ntr;
				c_line = c_line->next;
			}
			ft_putstr(buff);
		}
		if ((curs = curs->next) != NULL)
			ft_putchar('\n');
	}
	return (replace_i(ntr));
}

static int					creat_new_line(t_line **lines, char c)
/*
**	creat un nouveau maillon de liste chainee pour recevoir la nouvelle ligne (commande sur plusieurs lignes avec des quotes simple ou double)
*/
{
	t_line					*new;

	if (c != '\n')
		return (false);
	if (lines == NULL || *lines == NULL || g_lines == NULL)
		return (ERROR);
	if ((new = ft_memalloc(sizeof(t_line))) == NULL)
		return (ERROR);
	(*lines)->next = new;
	(*lines) = (*lines)->next;
	return (true);
}

static int					get_line_cmd(void)
/*
**	fonction qui place le curseur au debut du promt ajoute le caractere et ecrit le promt suivait des lignes
*/
{
	char					c;
	int						ret;

	while (1)
	{
		ft_putendl_fd("PASSLA", 2);
		if ((c = get_char_keyboard()) != KEY_IGNORE)
		{
			if (place_curs() == ERROR)
				return (ERROR);
			if (creat_new_line(&g_curs, c) == false)
				if (add_c_to_line(c, &g_curs) == ERROR)
					return (ERROR);
			if (put_cmd() == ERROR)
				return (ERROR);
		}
		if ((ret = is_end(c)) != false)
			break ;
	}
	return (ret);
}

static int					save_y_x_line2(t_entry *curs, size_t *x, size_t *y)
/*
**	sauvegarde les coordonnees du caractere qui vient detre ajoute je ne sais plus pk j'ai une variante avec save_y_x_line
*/
{
	size_t					mem_x;
	size_t					mem_y;
	t_entry					*tmp;
	t_21sh					*sh;

	sh = get_21sh(NULL);
	if ((tmp = curs) == NULL || x == NULL || y == NULL || sh == NULL)
		return (ERROR);
	mem_x = 0;
	mem_y = (*y) + 1;
	if (tmp->next != NULL)
		while (tmp != NULL)
		{
			mem_x = tmp->x_i;
			mem_y = tmp->y_i;
			//fprintf(debug, "a tmp %p \n ", tmp);
			if (tmp->x_i == 0)
				return (true);
			//fprintf(debug, "b tmp %p\n", tmp);
			tmp = tmp->next;
		}
	(*x) = mem_x;
	(*y) = mem_y;
	return (true);
}

int							save_y_x_line(t_line **lines, char c)
/*
**	calcul et sauvegarde les coordonnees du caractere ajoute
**	ULONG_MAX est normal, il y a 1 d'ajoute au valeurs x et x_i donc ca fait 0
*/
{
	static bool				prev_enter = false;
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) == NULL || lines == NULL || *lines == NULL ||
			sh->win.ws_col == 0)
		return (ERROR);
	if ((*lines)->curs != NULL && (*lines)->curs->prev != NULL && (*lines)->curs->prev->c == '\n')
	{
		if (save_y_x_line2((*lines)->curs, &(*lines)->x, &(*lines)->y) == ERROR)
			return (ERROR);
		(*lines)->x_i = 0;
		(*lines)->y_i = (*lines)->curs->prev->y_i + 1;
		return (true);
	}
	(*lines)->x = (*lines)->i == 0 && g_lines != g_curs ? ULONG_MAX : (*lines)->x;
	(*lines)->x_i = (*lines)->i == 0 && g_lines != g_curs ? ULONG_MAX : (*lines)->x_i;
	(*lines)->y_i = (*lines)->x_i + 1 >= sh->win.ws_col ? (*lines)->y_i + 1 : (*lines)->y_i;
	(*lines)->x_i = (*lines)->x_i + 1 >= sh->win.ws_col ? 0 : (*lines)->x_i + 1;
	return (true);
}

static int					init_x_y_i(size_t *x, size_t *y, size_t *i,
		t_line **lines)
/*
**	jsute pour gagner de la place dans la focntion du dessous
*/
{
	if (x == NULL || y == NULL || i == NULL || lines == NULL || *lines == NULL)
		return (ERROR);
	(*x) = (*lines)->x_i;
	(*y) = (*lines)->y_i;
	(*i) = (*lines)->i;
	return (true);
}

static int					save_coord_c_next(t_line **lines)
/*
**	saremplace les coordonnes des caracteres qui suivent le caractere qui vient d'etre ajoute
*/
{
	size_t					x;
	size_t					y;
	size_t					i;
	t_entry					*curs;
	t_21sh					*sh;

	if (lines == NULL || *lines == NULL || (*lines)->curs == NULL ||
		(sh = get_21sh(NULL)) == NULL || init_x_y_i(&x, &y, &i, lines) == ERROR)
		return (ERROR);
	curs = (*lines)->curs;
	while (curs != NULL)
	{
		curs->i = i++;
		x = curs->prev != NULL && curs->prev->c == '\n' && curs != (*lines)->curs ? 0 : x;
		y = curs->prev != NULL && curs->prev->c == '\n' && curs != (*lines)->curs ? y + 1 : y;
		curs->x_i = x;
		curs->y_i = y;
		(*lines)->x = curs->x_i;
		(*lines)->y = curs->y_i;
		y = x + 1 >= sh->win.ws_col ? y + 1 : y;
		x = x + 1 >= sh->win.ws_col ? 0 : x + 1;
		//fprintf(debug, "     %p                  x_i = %3zu y_i = %3zu, i = %3zu\n", curs, curs->x_i, curs->y_i, curs->i);
		curs = curs->next;
	}
	fprintf(debug, "x = %3zu, y = %3zu x_i = %3zu y_i = %3zu, i = %3zu, len = %3zu b\n", (*lines)->x, (*lines)->y, (*lines)->x_i, (*lines)->y_i, (*lines)->i, (*lines)->len);
	//fprintf(debug, "\n\n");
	return (true);
}

static int					check_save_y_x(t_line **lines, char c)
/*
**	sauvegarde le i et la len de la ligne sauvegarde le x_i et y_i de la ligne
*/
{
	if (lines == NULL || *lines == NULL)
		return (ERROR);
	(*lines)->i = ((*lines)->len == 0) ? 0 : (*lines)->i + 1;
	(*lines)->len++;
	if (save_y_x_line(lines, c) == ERROR)
		return (ERROR);
	return (save_coord_c_next(lines));
}

int							add_c_to_line(char c, t_line **line)
/*
**	ajoute le caractere a la ligne sauvegarde les coordonnes du caractere et des suivant
*/
{
	t_entry					*n;

	if ((n = ft_memalloc(sizeof(*n))) == NULL || line == NULL || *line == NULL)
		return (ERROR);
	if (c == '\n')
		fprintf(debug, "\\n = %p ", n);
	else
		fprintf(debug, "%2c = %p ", c, n);
	n->c = c;
	if ((*line)->curs == NULL)
	{
		(*line)->curs = n;
		(*line)->i = ULONG_MAX;
		if ((n->next = (*line)->line) != NULL)
			(*line)->line->prev = n;
		(*line)->line = n;
	}
	else
	{
		if ((*line)->curs->next != NULL)
			(*line)->curs->next->prev = n;
		n->next = ((*line)->curs->next != NULL) ? (*line)->curs->next : NULL;
		(*line)->curs->next = n;
		n->prev = (*line)->curs;
		(*line)->curs = (*line)->curs->next;
	}
	return (check_save_y_x(line, c));
}

static char					*save_tab(char *tab)
/*
**	sauvegarde dans un tableau l'ensemble de la listes chainees des lignes
*/
{
	size_t					i;
	t_line					*curs;
	t_entry					*curent_c;

	if((curs = g_lines) == NULL || tab == NULL)
		return (NULL);
	i = 0;
	while (curs != NULL)
	{
		curent_c = curs->line;
		while (curent_c != NULL)
		{
			if (curent_c->c != '\n')
				tab[i++] = curent_c->c;
			curent_c = curent_c->next;
		}
		if ((curs = curs->next) != NULL)
			tab[i++] = '\n';
	}
	del_g_lines();
	return(tab);
}

int							insert_word_in_g_line(char *word, t_line **line)
/*
**	ajoute a la position du curseur une string dans line
*/
{
	unsigned int			i;

	if (word == NULL || line == NULL || *line == NULL)
		return (ERROR);
	if (ft_strlen(word) > 0)
	{
		i = 0;
		while (word[i++] != '\0')
			if (word[i - 1] != '\n' || word[i] != '\0')
				if (add_c_to_line(word[i - 1], line) == ERROR)
					return (ERROR);
	}
	return (true);
}

static int					place_curs_end_line(void)
/*
**	place le curseur a la fin de l'ensemble des lignes
*/
{
	size_t					i;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ERROR);
	while (curs->next != NULL)
		curs =  curs->next;
	i = curs->y_i;
	while (i++ < curs->y)
		if (put_cmd_term("do") == ERROR)
			return (ERROR);
	i = curs->x_i;
	while (i++ < curs->x)
		if (put_cmd_term("nd") == ERROR)
			return (ERROR);
	return (true);
}


static int					save_y_x(void)
/*
**	cette fonction n'est plus utilisee. elle sauvegarde dans 2 variable globale les coordonnees de fin des lignes (les coordonnees du dernier caractere de la ligne)
*/
{
	size_t					i;
	t_line					*curs;

	g_y = 0;
	g_x = 0;
	if ((curs = g_lines) == NULL)
		return (ERROR);
	i = 0;
	while (curs != NULL)
	{
		g_y += curs->y;
		i++;
		g_x = curs->x;
		curs = curs->next;
	}
	if (i > 0)
		g_y += i - 1;
	return (place_curs_end_line());
}

char						*make_tab(void)
/*
**	transforme les g_lines en un tableau 1 dimension
*/
{
	char					*tab;
	size_t					len_total;
	t_line					*curs;

	if ((curs = g_lines) == NULL)
		return (ft_strdup(""));
	if (save_y_x() == ERROR)
		return (NULL);
	len_total = g_lines->count_line;
	while (curs != NULL)
	{
		len_total += curs->len;
		curs = curs->next;
	}
	if ((tab = ft_memalloc(sizeof(*tab) * (len_total + 1))) == NULL)
		return (NULL);
	return (save_tab(tab));
}


char						*get_line_entree(void)
/*
**	main qui gere la nouvelle ligne qui sera entree
*/
{
	t_21sh					*sh;

	if ((sh =get_21sh(NULL)) == NULL)
		return (NULL);
	del_g_lines();
	if ((g_lines = ft_memalloc(sizeof(t_line))) == NULL)
		return (NULL);
	g_curs = g_lines;
	g_curs->x = (sh->len_prompt - 1) % sh->win.ws_col;
	g_curs->x_i = (sh->len_prompt - 1) % sh->win.ws_col;
	g_curs->y = (sh->len_prompt - 1) / sh->win.ws_col;
	g_curs->y_i = (sh->len_prompt - 1) / sh->win.ws_col;
	if (get_line_cmd() == ERROR)
		return (NULL);
	ft_putendl_fd("passsssssssssssssss", 2);
	return (make_tab());
}
