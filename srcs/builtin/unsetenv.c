/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 19:32:24 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/03 22:50:54 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/shell_21sh.h"
#include "../incs/key.h"

static int				ft_put_error(void)
{
	ft_putstr_fd("The name argument is a null pointer, ", STDERR_FILENO);
	ft_putstr_fd("points to an empty string, or points ", STDERR_FILENO);
	ft_putendl_fd("to a string containing an '=' character.", STDERR_FILENO);
	return (ERROR);
}

static void				del_env_(t_env **env)
{
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = NULL;
}

static void				loop_check(t_env **env, t_env **env_next, char *arg)
{
	t_21sh				*sh;

	sh = get_21sh(NULL);
	while (*env_next)
	{
		if (ft_strequ((*env_next)->name, arg))
		{
			if (ft_strequ(arg, "PATH"))
				del_bin();
			(*env)->next = (*env_next)->next;
			del_env_(env_next);
			sh->nb_var_env--;
			break ;
		}
		*env = (*env)->next;
		*env_next = (*env_next)->next;
	}
}

int						builtin_unsetenv(t_cmd *content)
{
	t_21sh	*sh;
	t_env	*env;
	t_env	*env_next;

	env = NULL;
	env_next = NULL;
	if ((len_y(content->arg) == 1) ||
			((len_y(content->arg) > 1) && ft_strchr(content->arg[1], '=')))
		return (ft_put_error());
	if ((sh = get_21sh(NULL)) == NULL || sh->env == NULL)
		return (ERROR);
	env = sh->env;
	env_next = sh->env->next;
	if (ft_strequ(env->name, content->arg[1]))
	{
		if (ft_strequ(content->arg[1], "PATH"))
			del_bin();
		sh->env = env->next;
		del_env_(&env);
		sh->nb_var_env--;
	}
	else
		loop_check(&env, &env_next, content->arg[1]);
	return (true);
}
