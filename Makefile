#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/05/17 16:07:18 by fpasquer          #+#    #+#             *#
#*   Updated: 2016/10/24 15:09:46 by fcapocci         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME			= 21sh

SRC_NAME		= main.c init_21sh.c fonctions.c bin.c table_hash.c del_bin.c	\
					sort_fonctions.c sort_list.c env.c builtin_env.c key.c		\
					parse.c parse2.c setenv.c add_env_.c unsetenv.c  			\
					exe_binaire.c linked_list_to_array_env.c builtin_exit.c		\
					quotes.c split_quotes.c redirection.c						\
					redirection2.c exe_binaire2.c history.c						\
					print_list_term.c functions_signaux.c options_env.c			\
					options_env2.c loop_shell.c term.c							\
					cd.c builtin_or_not.c getenv_value.c						\
					modify_env_value.c check_if_env_exist.c dico.c				\
					print_event.c del_g_lines.c list_bin.c autocompletion.c		\
					get_and_del_21sh.c event_del.c event_move.c

INCLUDES		= shell_21sh.h key.h

LIBRARY			= libft/libft.a

OTHERS			= libft Makefile auteur

OTHER_FLAGS 	= -lncurses

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
OBJ_NAME		= $(SRC_NAME:.c=.o)

SRCDIR_BIN		= srcs/bin
SRCDIR_BUILTIN	= srcs/builtin
SRCDIR_COMPLET	= srcs/completion
SRCDIR_ENV		= srcs/env
SRCDIR_EXE_CMD	= srcs/exe_cmd
SRCDIR_HISTORY	= srcs/history
SRCDIR_KEYBORD	= srcs/keybord
SRCDIR_PARSE	= srcs/parse
SRCDIR_SHELL	= srcs/shell
SRCDIR_SIG		= srcs/sig

OBJDIR			= objs
INCDIR			= incs

SRC				= $(addprefix $(SRCDIR)/, $(SRC_NAME))
OBJ				= $(addprefix $(OBJDIR)/, $(OBJ_NAME))
INC				= $(addprefix $(INCDIR)/, $(INCLUDES))
DATE			= `date +'%d/%m/%y %H:%M:%S'`

All : $(NAME)

$(NAME) : $(OBJDIR) $(OBJ) $(LIBRARY)
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBRARY) $(OTHER_FLAGS)
	@echo "\033[0;32m"$(NAME) "DONE\033[0m"

$(LIBRARY) :
	@echo "\033[0;32mCOMPILE LIBFT\033[0m"
	make -C libft

$(OBJDIR)/%.o : $(SRCDIR_BIN)/%.c $(INC)
	@echo "\033[0;32mCOMPILE BIN\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(SRCDIR_BUILTIN)/%.c $(INC)
	@echo "\033[0;32mCOMPILE BUILTIN\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(SRCDIR_COMPLET)/%.c $(INC)
	@echo "\033[0;32mCOMPILE COMPLETION\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(SRCDIR_ENV)/%.c $(INC)
	@echo "\033[0;32mCOMPILE ENV\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(SRCDIR_EXE_CMD)/%.c $(INC)
	@echo "\033[0;32mCOMPILE CMD\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(SRCDIR_HISTORY)/%.c $(INC)
	@echo "\033[0;32mCOMPILE HISTORY\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLA) -o $@ -c $< #REMETTRE LES FLAGS QUAND FICHIERS OK

$(OBJDIR)/%.o : $(SRCDIR_KEYBORD)/%.c $(INC)
	@echo "\033[0;32mCOMPILE KEYBORD\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLA) -o $@ -c $< #REMETTRE LES FLAGS QUAND FICHIERS OK

$(OBJDIR)/%.o : $(SRCDIR_PARSE)/%.c $(INC)
	@echo "\033[0;32mCOMPILE PARSE\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(SRCDIR_SHELL)/%.c $(INC)
	@echo "\033[0;32mCOMPILE SHELL\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o : $(SRCDIR_SIG)/%.c $(INC)
	@echo "\033[0;32mCOMPILE SIG\033[0m"
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf $(OBJDIR)
	make -C libft fclear

re : fclean All

norm:
	norminette $(SRC) $(INC)
