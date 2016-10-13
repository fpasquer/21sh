#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int 		builtin_unsetenv(t_cmd *content) {
	if (content->argc == 1 || (content->argc > 1 && ft_strchr(content->arg[1], '='))) {
		ft_putendl("The name argument is a null pointer, points to an empty string, or points to a string containing an '=' character.");
	}
	return (true);
}