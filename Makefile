# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 05:43:04 by kamin             #+#    #+#              #
#    Updated: 2022/07/18 21:08:52 by ommohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCLUDES	=	./includes

DIR_S		=	./src/

SRC		=	builtins/env.c \
			builtins/echo.c \
			builtins/pwd.c \
			execution/exec.c \
			main.c \
			history/history.c \
			redirection/redirection.c \
			redirection/get_next_line.c \
			redirection/get_next_line_utils.c \
			signals/signals.c \

OBJS	=	$(addprefix $(DIR_S),$(SRC:.c=.o))

CC		=	gcc -fcommon

CFLAGS	=	-Wall -Werror -Wextra -g3



all:	$(NAME)

$(NAME): $(OBJS) libft.a parser.a
		$(CC) $(CFLAGS) $(OBJS) libft.a  parser -I$(INCLUDES) -lreadline -o $(NAME)

libft.a: 
		@$(MAKE) -C libft
		@mv libft/libft.a libft.a
		@echo "Make libft successful"

parser.a:
		@$(MAKE) -C src/parser
		@mv src/parser/parser parser
		@echo "Make parser successful"
		

clean:
		make clean -C src/parser
		rm -f $(OBJS)

fclean: clean
		make fclean -C src/parser
		rm -f $(NAME)
		rm -f libft.a
		rm -f libft/*.o
		rm -f libft/libft.a
		rm -f parser

re:		fclean all

.PHONY: libft.a parser.a $(NAME)