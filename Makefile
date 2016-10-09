#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/05/17 16:07:18 by fpasquer          #+#    #+#             *#
#*   Updated: 2016/09/30 13:05:40 by fpasquer         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME			= 21sh

SRC_NAME		= main.c init_21sh.c fonctions.c bin.c table_hash.c del_bin.c	\
					sort_fonctions.c sort_list.c env.c builtin_env.c			\
					options_env.c loop_shell.c

INCLUDES		= shell_21sh.h

LIBRARY			= libft/libft.a

OTHERS			= libft Makefile auteur

OTHER_FLAGS 	= -lncurses

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
OBJ_NAME		= $(SRC_NAME:.c=.o)

SRCDIR			= srcs
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
	make -C libft

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	$(GCC) -I $(INCDIR)/ $(CFLAG) -o $@ -c $<

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

#push : fclean
#	git add $(SRCDIR) $(INCDIR) $(OTHERS) ./libft
#	git commit -m "$(DATE)"
#	echo "Enter Your Commit : "
#	read root_path ; git commit -m "$$root_path"
#	git push

norm:
	norminette $(SRC) $(INC)
