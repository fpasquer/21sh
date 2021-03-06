/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 08:36:05 by fpasquer          #+#    #+#             */
/*   Updated: 2016/10/10 20:38:25 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include <stdio.h>

int							add_env(t_env **env, char *str, int index, bool add)
{
	char					*egal;
	t_env					*new;
	t_env					*curs;

	if (env == NULL || str == NULL)
		return (ERROR);
	if ((new = ft_memalloc(sizeof(*new))) == NULL)
		return (ERROR);
	if ((egal = ft_strchr(str, '=')) == NULL)
		return (ERROR);
	*egal = '\0';
	if ((new->name = ft_strdup(str)) && (new->value = ft_strdup(egal + 1)))
	{
		new->index = index;
		new->add = add;
		if ((curs = *env) == NULL)
			*env = new;
		else
		{
			while (curs->next != NULL)
				curs = curs->next;
			curs->next = new;
		}
	}
	return ((new == NULL) ? ERROR : true);
}

int							save_env(t_env **env)
{
	extern char				**environ;
	int						i;

	if (env == NULL || environ == NULL)
		return (ERROR);
	i = 0;
	while (environ[i++] != NULL)
		if (add_env(env, environ[i - 1], i - 1, true) == ERROR)
			return (ERROR);
	return (i - 1);
}

int							del_list_env(t_env **list)
{
	t_env					*curs;
	t_env					*mem;

	if (list == NULL)
		return (ERROR);
	curs = *list;
	while (curs != NULL)
	{
		mem = curs->next;
		ft_memdel((void**)&curs->name);
		ft_memdel((void**)&curs->value);
		ft_memdel((void**)&curs);
		curs = mem;
	}
	return (true);
}

int							del_env(void)
{
	t_21sh					*sh;

	if ((sh = get_21sh(NULL)) != NULL)
		return (del_list_env(&sh->env));
	return (false);
}
