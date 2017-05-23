/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:37:23 by fpasquer          #+#    #+#             */
/*   Updated: 2017/05/23 17:35:41 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

//#define C_S ' '
//#define C_W_Q '"'
//#define C_S_Q '\''
//#define C_HT '\t'

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
		if (str[i] != '\t')
		{
			new_str[count] = str[i];
			count++;
		}
		i++;
	}
	return (check_globbing(&new_str, nb_ht));
}

static char			*parse_string(char *s, int *i, char d, int nb)
{
	int				start_index;

	if (s[*i] != '\''  && s[*i] != '"')
		d = ' ';
	else
		(*i)++;
	start_index = (*i);
	while (s[*i] && s[*i] != d)
	{
		if ((s[*i] == '\'' || s[*i] == '"') && d == ' ')
		{
			d = s[*i];
			s[*i] = '\t';
			nb++;
		}
		(*i)++;
		if ((s[*i] == '\t' && d == '\t') || (s[*i] == '"' && d == '"'))
		{
			s[*i] = '\t';
			d = ' ';
			(*i)++;
			nb++;
		}
	}
	return (ft_strsub_bis(s, start_index, *i, nb));
}
/*static char			*parse_string(char *s, int *i, char d, int nb)
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
}*/


char				**split_quotes(char *str)
{
	int				i;
	int				len;
	char			**list;
	char			*new_str;
	char			*tmp_str;

	i = 0;
	list = NULL;
	new_str = NULL;
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	tmp_str = ft_strdup(str);
	while (i < len)
	{
		if (tmp_str[i] != ' ')
		{
			new_str = parse_string(tmp_str, &i, str[i], 0);
			fprintf(debug, "new_str = %s\n", new_str);
			list = ft_add_to_array(new_str, list);
		}
		i++;
	}
	free(tmp_str);
	return (list);
}
