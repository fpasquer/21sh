#include "../../incs/shell_21sh.h"
#include "../../incs/key.h"

int cd_change_pwd (char *path) {
	char *new_path;
	char *old_pwd;
	t_21sh *sh;

	if ((sh = get_21sh(NULL)) == NULL)
		return (false);

	old_pwd = getcwd(NULL, 0);

	if (chdir(path) == ERROR)
		return (false);

	new_path = getcwd(NULL, 0);

	/*
	** CHANGE PWD
	** EN VERIFIANT SI OLD_PWD EST SET
	*/
	
	if (check_if_env_exist("PWD") == false) {
		if (add_env(&sh->env, new_path, ++sh->nb_var_env, true) == ERROR)
			return (false);
	}
	else if (modify_env_value("PWD", new_path) == false) {
		return (false);
	}

	/*
	** CHANGE OLD PWD
	** EN VERIFIANT SI OLWD_PWD EST SET
	*/

	if (check_if_env_exist("OLDPWD") == false) {
		if (add_env(&sh->env, old_pwd, ++sh->nb_var_env, true) == ERROR)
			return (false);
	}
	else if (modify_env_value("OLDPWD", old_pwd) == false) {
		return (false);
	}

	free(new_path);
	free(old_pwd);
	return (true);
}

int check_if_valid_path (char *path) {
	t_stat information;

	if (lstat(path, &information) == -1) {
		return (false);
	}
	if (information.st_mode & S_IFREG) {
		ft_putstr("cd: not a directory: ");
		ft_putendl(path);
	}
	else if (access(path, R_OK) == ERROR) {
		ft_putstr("cd: permission denied: ");
		ft_putendl(path);
	}
	return (true);
}

int cd_home () {
	char *path;

	if (!check_if_env_exist("HOME")) {
		ft_putendl("cd: HOME not set");
	}
	else {
		if ((path = getenv_value("HOME")) == NULL)
			return (false);
		cd_change_pwd(path);
	}
	return (true);
}

int cd_less () {
	char *path;

	if (!check_if_env_exist("OLDPWD")) {
		ft_putendl("cd: OLDPWD not set");
	}
	else {
		if ((path = getenv_value("OLDPWD")) == NULL)
			return (false);
		path = ft_strdup(path);
		cd_change_pwd(path);
		free(path);
	}
	return (true);
}

int cd (t_cmd *content) {
	char *path = NULL;

	if (content->argc > 1) {
		path = content->arg[1];
	}
	if (content->argc == 1)
		return (cd_home());
	else if (path && ft_strequ("-", path))
		return (cd_less());
	else if (check_if_valid_path(path)) {
		return (cd_change_pwd(path));
	}
	else {
		ft_putstr("cd: ");
		ft_putstr(path);
		ft_putendl(": No such file or directory");
	}
	return (1);
}