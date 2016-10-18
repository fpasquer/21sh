#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

# define w_quotes 	1
# define s_quotes 	2
# define space		3

# define CHAR_SPACE 32
# define CHAR_W_QUOTE 34
# define CHAR_S_QUOTE 39

/*
**
**	fonction qui renvoit un tableau de 
**	char ** decoupant la chaine a chaque espace
**	en regroupant les chaines sous "guillement".
**
**	w_quotes = weak quotes "
**	s_quotes = strong quotes '
**
*/

static char **add_to_array(char *str, char **list) {
	char **new_list = NULL;

	if (ft_strlen(str) == false) {
		return (list);
	}
	int len_list = len_y(list);
	int i = 0;
	if ((new_list = (char**)malloc(sizeof(char*) * (len_list + 2))) == NULL)
		return (NULL);
	if (len_list > 0) {
		while (list[i]) {
			new_list[i] = list[i];
			i++;
		}
	}
	new_list[i++] = str;
	new_list[i] = NULL;
	if (list) {
		free(list);
	}
	return (new_list);
}

static char **malloc_quotes(char *str, int *index, char **list, char delimiter) {
	char **new_list = NULL;
	(*index)++;
	int start_index = (*index);

	while (str[*index] && str[*index] != delimiter) {
		(*index)++;
	}
	char *new_str = ft_strsub(str, start_index, (*index) - start_index);
	new_list = add_to_array(new_str, list);
	return (new_list);
}

static char **malloc_string_to_space(char *str, int *index, char **list, char delimiter) {
	char **new_list = NULL;
	int start_index = (*index);

	while (str[*index] && str[*index] != delimiter) {
		if ((str[*index] == CHAR_S_QUOTE || str[*index] == CHAR_W_QUOTE) && delimiter == CHAR_SPACE) {
			delimiter = str[*index];
		}
		(*index)++;
		if ((str[*index] == CHAR_S_QUOTE && delimiter == CHAR_S_QUOTE) || 
				(str[*index] == CHAR_W_QUOTE && delimiter == CHAR_W_QUOTE)) {
			delimiter = CHAR_SPACE;
			(*index)++;
		}
	}
	char *new_str = ft_strsub(str, start_index, (*index) - start_index);
	new_list = add_to_array(new_str, list);
	return (new_list);
}

char **split_quotes(char *str) {
	int i = 0;
	int len = ft_strlen(str);
	char **new_list = NULL;

	if (str == NULL) {
		return NULL;
	}
	while (i < len) {
		if (str[i] != CHAR_SPACE) {
			if (str[i] == CHAR_W_QUOTE || str[i] == CHAR_S_QUOTE) {
				new_list = malloc_quotes(str, &i, new_list, str[i]);
			}
			else {
				new_list = malloc_string_to_space(str, &i, new_list, CHAR_SPACE);
			}
		}
		i++;
	}
	return (new_list);
}