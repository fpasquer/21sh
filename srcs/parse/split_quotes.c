/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:37:23 by fcapocci          #+#    #+#             */
/*   Updated: 2017/04/12 14:55:58 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

#define C_S 	32
#define C_W_Q 	34
#define C_S_Q 	39
#define C_HT		9

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
		if (str[i] != C_HT)
		{
			new_str[count] = str[i];
			count++;
		}
		i++;
	}
	return (new_str);
}

static char			*parse_string(char *s, int *i, char d, int nb)
{
	int				start_index;

	if (s[*i] != C_S_Q && s[*i] != C_W_Q)
		d = C_S;
	else
		(*i)++;
	start_index = (*i);
	while (s[*i] && s[*i] != d)
	{
		if ((s[*i] == C_S_Q || s[*i] == C_W_Q) && d == C_S)
		{
			d = s[*i];
			s[*i] = C_HT;
			nb++;
		}
		(*i)++;
		if ((s[*i] == C_S_Q && d == C_S_Q) || (s[*i] == C_W_Q && d == C_W_Q))
		{
			s[*i] = C_HT;
			d = C_S;
			(*i)++;
			nb++;
		}
	}
	return (ft_strsub_bis(s, start_index, *i, nb));
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
		if (tmp_str[i] != C_S)
		{
			new_str = parse_string(tmp_str, &i, str[i], 0);
			list = ft_add_to_array(new_str, list);
		}
		i++;
	}
	free(tmp_str);
	return (list);
}
