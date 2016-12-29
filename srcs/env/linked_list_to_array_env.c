/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_to_array_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:08:27 by fcapocci          #+#    #+#             */
/*   Updated: 2016/12/29 17:11:56 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

char				**l_l_to_arr_env(void)
{
	t_21sh			*sh;
	t_env			*env;
	char			**new_env;
	int				i;

	i = 0;
	if ((sh = get_21sh(NULL)) == NULL)
		return (NULL);
	env = sh->env;
	if ((new_env = ft_memalloc(sizeof(char*) * (sh->nb_var_env + 1))) == NULL)
		return (NULL);
	while (env)
	{
		if ((new_env[i] = ft_multijoin(3, env->name, "=", env->value)) == NULL)
			break ;
		env = env->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int					delete_env_array(char **env)
{
	int				i;

	i = 0;
	if (!env)
		return (false);
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (true);
}
