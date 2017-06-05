/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exclame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:33:53 by fcapocci          #+#    #+#             */
/*   Updated: 2017/06/03 19:54:50 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

#define G_C_C g_curs->curs
#define P prev

static int					last_token(void)
{
	int						ret;

	if (g_curs == NULL || G_C_C == NULL || G_C_C->P == NULL)
		return (ERROR);
	ret = 24;
	if (G_C_C->P->P && G_C_C->P->c == '!' && G_C_C->P->P->c == '!')
		while (ret-- > 21)
			del_left();
	return (ret);
}

static int					builtin_exclame(void)
{
	t_21sh				*sh;
	char				*tmp;

	if ((sh = get_21sh(NULL)) == NULL)
		return (false);
	if (sh->hist == NULL)
	{
		ft_putendl_fd("error: !!: event not found", STDERR_FILENO);
		print_prompt();
		return (false);
	}
	else
	{
		if (sh->hist->line)
		{
			tmp = ft_trim(sh->hist->line);
			place_curs();
			insert_word_in_g_line(tmp, &g_curs);
			ft_memdel((void**)&tmp);
		}
	}
	return (true);
}

int							check_words_builtins_exclame(char c)
{
	if (c != ' ')
		return (false);
	else if (last_token() == 20)
		return (builtin_exclame());
	else
		return (false);
}
