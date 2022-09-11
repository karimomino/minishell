# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 05:43:04 by kamin             #+#    #+#              #
#    Updated: 2022/09/11 16:54:53 by ommohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCLUDES	=	./includes

DIR_S		=	./src/

SRC		=	builtins/env.c \
			builtins/echo.c \
			builtins/pwd.c \
			builtins/cd.c \
			builtins/exit.c \
			builtins/utils.c \
			environment/environment.c \
			execution/exec.c \
			main.c \
			history/history.c \
			redirection/redirection.c \
			redirection/redirection_in.c \
			redirection/get_next_line.c \
			redirection/get_next_line_utils.c \
			signals/signals.c \
			pipe/pipe.c

OBJS	=	$(addprefix $(DIR_S),$(SRC:.c=.o))

prefix		=	/opt/homebrew/Cellar/readline/8.1.2
# prefix		=	/usr/local/Cellar/readline/8.1
exec_prefix	=	${prefix}
libdir		=	${exec_prefix}/lib
includedir	=	${prefix}/include
LDFLAGS 	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib
CFLAGS		=	-Wall -Wextra -Werror -g3 -I${includedir}
LDFLAGS 	=	-lreadline -L${libdir}


CC		=	gcc -fcommon

all:	$(NAME)

$(NAME): .printing_obj $(OBJS) libft.a parser.a .clear
		@$(CC) $(CFLAGS) $(OBJS) libft.a parser.a -I$(INCLUDES) $(LDFLAGS) -o $(NAME)
		@echo "Compilation Successful!"

.printing_obj:
			@echo "Compiling OBJECT Files..."

.clear:
			@clear

libft.a:
		@echo "Compiling LIBFT Files..."
		@$(MAKE) -C libft -s
		@clear
		@mv libft/libft.a libft.a

parser.a:
		@echo "Compiling PARSER Files..."
		@$(MAKE) -C src/parser -s
		@clear
		@mv src/parser/parser.a parser.a


all:	$(NAME)

clean:
		@make clean -C src/parser -s
		@rm -f $(OBJS)

fclean: clean
		@$(MAKE) fclean -C libft -s
		@make fclean -C src/parser -s
		@rm -f $(NAME)
		@if [ -f src/history/.history ]; then rm src/history/.history; fi

re:		fclean all

.PHONY: all re clean fclean libft.a parser
