/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcapocci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:52:55 by fcapocci          #+#    #+#             */
/*   Updated: 2017/02/25 20:49:10 by fcapocci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

static int			cd_change_pwd(char *path)
{
	char			*new_path;
	char			*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == ERROR)
		return (false);
	new_path = getcwd(NULL, 0);
	if (check_if_env_exist("PWD", NULL) == false)
	{
		if (add_env_("PWD", new_path) == ERROR)
			return (false);
	}
	else if (modify_env_value("PWD", new_path) == false)
		return (false);
	if (check_if_env_exist("OLDPWD", NULL) == false)
	{
		if (add_env_("OLDPWD", old_pwd) == ERROR)
			return (false);
	}
	else if (modify_env_value("OLDPWD", old_pwd) == false)
		return (false);
	free(new_path);
	free(old_pwd);
	return (true);
}

static int			check_if_valid_path(char *path)
{
	t_stat			information;

	if (lstat(path, &information) == -1)
		return (false);
	if (information.st_mode & S_IFREG)
	{
		ft_putstr_fd("cd: not a directory: ", STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
	}
	else if (access(path, R_OK) == ERROR)
	{
		ft_putstr_fd("cd: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
	}
	return (true);
}

static int			cd_home(void)
{
	char			*path;

	if (!check_if_env_exist("HOME", NULL))
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (false);
	}
	else
	{
		if ((path = getenv_value("HOME")) == NULL)
			return (false);
		cd_change_pwd(path);
	}
	return (true);
}

static int			cd_less(void)
{
	char			*path;

	if (!check_if_env_exist("OLDPWD", NULL))
	{
		ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
		return (false);
	}
	else
	{
		if ((path = getenv_value("OLDPWD")) == NULL)
			return (false);
		path = ft_strdup(path);
		cd_change_pwd(path);
		free(path);
	}
	return (true);
}

int					cd(t_cmd *content)
{
	char			*path;

	path = NULL;
	if (content->arg && (len_y(content->arg) > 1))
		path = content->arg[1];
	if (content->arg && (len_y(content->arg) == 1))
		return (cd_home());
	else if (path && ft_strequ("-", path))
		return (cd_less());
	else if (check_if_valid_path(path))
		return (cd_change_pwd(path));
	else
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (false);
	}
	return (true);
}
