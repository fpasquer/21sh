#include "../incs/shell_21sh.h"
#include "../incs/key.h"

int				count(char **cmd_argv) {
	int 		i;

	i = 0;
	while (cmd_argv[i]) {
		i++;
	}
	return (i);
}

t_stin_content	parse_stin(char *line) {
	t_stin_content cmd;

	ft_bzero(&cmd, sizeof(t_stin_content));
	cmd.bin_argv = ft_strsplit(line, SPACE_CHAR);
	if (cmd.bin_argv) {
		cmd.str = line;
		cmd.bin = cmd.bin_argv[0];
		cmd.bin_argc = count(cmd.bin_argv);
	}
	return (cmd);
}