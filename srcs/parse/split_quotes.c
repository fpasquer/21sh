/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:37:23 by fcapocci          #+#    #+#             */
/*   Updated: 2017/01/04 16:54:34 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

#define CHAR_SPACE 	32
#define CHAR_W_QUOTE 	34
#define CHAR_S_QUOTE 	39
#define CHAR_HT		9

/*
**	fonction qui renvoit un tableau de
**	char ** decoupant la chaine a chaque espace
**	en regroupant les chaines sous "guillement"
**	w_quotes = weak quotes "
**	s_quotes = strong quotes '
**	HT = horizontal tab
*/

static char			*ft_strsub_bis(char *str, int index, int end, int nb_ht)
{
	int				i;
	int				count;
	char			*new_str;

	i = index;
	count = 0;
	new_str = ft_strnew(end - index - nb_ht);
	while (i < end)
	{
		if (str[i] != CHAR_HT)
		{
			new_str[count] = str[i];
			count++;
		}
		i++;
	}
	return (new_str);
}

static char			*parse_string(char *str, int *index, char delimiter, int nb)
{
	int				start_index;

	if (str[*index] != CHAR_S_QUOTE && str[*index] != CHAR_W_QUOTE)
		delimiter = CHAR_SPACE;
	else
		(*index)++;
	start_index = (*index);
	while (str[*index] && str[*index] != delimiter)
	{
		if ((str[*index] == CHAR_S_QUOTE ||
				str[*index] == CHAR_W_QUOTE) && delimiter == CHAR_SPACE)
		{
			delimiter = str[*index];
			str[*index] = CHAR_HT;
			nb++;
		}
		(*index)++;
		if ((str[*index] == CHAR_S_QUOTE && delimiter == CHAR_S_QUOTE) ||
				(str[*index] == CHAR_W_QUOTE && delimiter == CHAR_W_QUOTE))
		{
			str[*index] = CHAR_HT;
			delimiter = CHAR_SPACE;
			(*index)++;
			nb++;
		}
	}
	return (ft_strsub_bis(str, start_index, *index, nb));
}

char				**split_quotes(char *str)
{
	int				i;
	int				len;
	char			**list;
	char			*new_str;
	char			*tmp_str;

	i = 0;
	len = ft_strlen(str);
	list = NULL;
	new_str = NULL;
	if (str == NULL)
		return (NULL);
	tmp_str = ft_strdup(str);
	while (i < len)
	{
		if (tmp_str[i] != CHAR_SPACE)
		{
			new_str = parse_string(tmp_str, &i, str[i], 0);
			list = ft_add_to_array(new_str, list);
		}
		i++;
	}
	free(tmp_str);
	return (list);
}
