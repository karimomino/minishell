# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 05:43:04 by kamin             #+#    #+#              #
#    Updated: 2022/07/11 16:58:42 by ommohame         ###   ########.fr        #
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

OBJS	=	$(addprefix $(DIR_S),$(SRC:.c=.o))

CC		=	gcc -fcommon

CFLAGS	=	-Wall -Werror -Wextra -g3

$(NAME): $(OBJS)
		@$(MAKE) -C libft
		@echo "Make libft successful"
		@mv libft/libft.a libft.a
		@$(MAKE) -C src/parser
		echo "Make parser successful"
		@mv src/parser/parser parser
		$(CC) $(CFLAGS) $(OBJS) libft.a parser -I$(INCLUDES) -lreadline -o $(NAME)

all:	$(NAME)

clean:
		make clean -C src/parser
		rm -f $(OBJS)

fclean: clean
		make fclean -C src/parser
		rm -f $(NAME)
		rm -f libft.a
		rm -f libft/*.o
		rm -f libft/libft.a

re:		fclean all
