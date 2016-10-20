#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

# define CHAR_SPACE 	32
# define CHAR_W_QUOTE 	34
# define CHAR_S_QUOTE 	39
# define CHAR_HT		9

/*
**
**	fonction qui renvoit un tableau de 
**	char ** decoupant la chaine a chaque espace
**	en regroupant les chaines sous "guillement".
**
**	w_quotes = weak quotes "
**	s_quotes = strong quotes '
** 	HT = horizontal tab
**
*/

static char *ft_strsub_bis(char *str, int index, int end, int nb_ht) {
	int i = index;
	int count = 0;
	char *new_str = ft_strnew(end - index - nb_ht);
	
	i = index;
	count = 0;
	while (i < end) {
		if (str[i] != CHAR_HT) {
			new_str[count] = str[i];
			count++;
		}
		i++;
	}
	return(new_str);
}

static char *parse_string(char *str, int *index, char delimiter) {
	
	if (str[*index] != CHAR_S_QUOTE && str[*index] != CHAR_W_QUOTE) {
		delimiter = CHAR_SPACE;
	}
	else {
		(*index)++;
	}
	int start_index = (*index);
	int nb_ht = 0;
	while (str[*index] && str[*index] != delimiter) {
		if ((str[*index] == CHAR_S_QUOTE || str[*index] == CHAR_W_QUOTE) && delimiter == CHAR_SPACE) {
			delimiter = str[*index];
			str[*index] = CHAR_HT;
			nb_ht++;
		}
		(*index)++;
		if ((str[*index] == CHAR_S_QUOTE && delimiter == CHAR_S_QUOTE) || 
				(str[*index] == CHAR_W_QUOTE && delimiter == CHAR_W_QUOTE)) {
			str[*index] = CHAR_HT;
			delimiter = CHAR_SPACE;
			(*index)++;
			nb_ht++;
		}
	}
	char *new_str = ft_strsub_bis(str, start_index, *index, nb_ht);
	return (new_str);
}

char **split_quotes(char *str) {
	int i = 0;
	int len = ft_strlen(str);
	char **list = NULL;
	char *new_str = NULL;
	
	if (str == NULL) {
		return NULL;
	}
	char *tmp_str = ft_strdup(str);
	while (i < len) {
		if (tmp_str[i] != CHAR_SPACE) {
				new_str = parse_string(tmp_str, &i, str[i]);
				list = ft_add_to_array(new_str, list);
		}
		i++;
	}
	free(tmp_str);
	return (list);
}
