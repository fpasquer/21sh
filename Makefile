#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/05/17 16:07:18 by fpasquer          #+#    #+#             *#
#*   Updated: 2016/10/26 20:09:27 by fpasquer         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME			= 21sh

SRC_NAME		= main.c init_21sh.c fonctions.c bin.c table_hash.c del_bin.c	\
					sort_fonctions.c sort_list.c env.c term.c dico.c history.c	\
					functions_signaux.c loop_shell.c key.c del_g_lines.c		\
					functions_key.c search_history.c autocompletion.c			\
					print_event.c print_list_term.c autocompletion_bin.c

INCLUDES		= shell_21sh.h key.h

LIBRARY			= libft/libft.a

OTHERS			= libft Makefile auteur

OTHER_FLAGS 	= -lncurses

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
OBJ_NAME		= $(SRC_NAME:.c=.o)

SRCDIR			= srcs
SRCDIR_BUILTIN	= srcs/builtin
SRCDIR_EXE_CMD	= srcs/exe_cmd
SRCDIR_ENV		= srcs/env
SRCDIR_PARSE	= srcs/parse
SRCDIR_TERMCAPS	= srcs/parse

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

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
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
