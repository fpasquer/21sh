/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 19:08:27 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/25 20:48:10 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

static int		ft_put_error(int choice)
{
	if (choice == 1)
	{
		ft_putstr_fd("Error: the name argument is a null ", STDERR_FILENO);
		ft_putendl_fd("pointer, or points to an empty string", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("Error: the name argument points to a ", STDERR_FILENO);
		ft_putendl_fd("string containing an '=' character.", STDERR_FILENO);
	}
	return (false);
}

int				builtin_setenv(t_cmd *content)
{
	t_21sh		*sh;
	char		*env_name;
	char		*env_value;

	if ((sh = get_21sh(NULL)) == NULL)
		return (ERROR);
	if (len_y(content->arg) == 1)
		return (ft_put_error(1));
	if (len_y(content->arg) > 1)
	{
		if (ft_strchr(content->arg[1], '=') || ft_strequ("", content->arg[1]))
			return (ft_put_error(2));
		env_name = len_y(content->arg) > 1 ? content->arg[1] : NULL;
		env_value = len_y(content->arg) > 2 ? content->arg[2] : NULL;
		if (check_if_env_exist(env_name, NULL) == false)
			add_env_(env_name, env_value);
		else
			modify_env_value(env_name, env_value);
		if (ft_strequ(env_name, "PATH"))
		{
			del_bin();
			save_path(&sh, content->arg[2]);
		}
	}
	return (true);
}
