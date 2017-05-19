/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 19:42:22 by fcapocci          #+#    #+#             */
/*   Updated: 2017/05/19 23:16:22 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/key.h"
#include "../incs/shell_21sh.h"
#include <term.h>

#define GL_SRCH g_lines->h_srch == true

static int					heredoc_prompt(t_21sh *sh)
{
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	sh->len_prompt = ft_strlen("search : ");
	return (true);
}

static int					search_prompt(t_21sh *sh)
{
	ft_putstr_fd("search : ", STDOUT_FILENO);
	sh->len_prompt = ft_strlen("search : ");
	return (true);
}

int							print_prompt(void)
{
	char					promt[SIZE_PROMT + 5];
	char					*ret;
	t_21sh					*sh;

	if ((ret = tgetstr("sc", NULL)) == NULL)
		return (false);
	tputs(ret, 0, my_out_put);
	if (getcwd(promt, SIZE_PROMT) == NULL || (sh = get_21sh(NULL)) == NULL)
		return (false);
	if (g_lines && GL_SRCH && g_lines->hdc == true)
		return (heredoc_prompt(sh));
	if (g_curs && GL_SRCH && (g_curs->line || g_curs == g_lines))
		return (search_prompt(sh));
	if (ft_strcat(promt, " ?> ") == NULL)
		return (false);
	ft_putstr_fd(COLOR_POMT, STDOUT_FILENO);
	ft_putstr_fd(promt, STDOUT_FILENO);
	ft_putstr_fd(RESET_COLOR, STDOUT_FILENO);
	sh->len_prompt = ft_strlen(promt);
	return (true);
}

int							clean_and_put_prompt(void)
{
	int						ret;

	ret = put_cmd_term("cd");
	print_prompt();
	return (ret);
}
