# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamin <kamin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 05:43:04 by kamin             #+#    #+#              #
#    Updated: 2022/07/18 17:49:14 by kamin            ###   ########.fr        #
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

OBJS	=	$(addprefix $(DIR_S),$(SRC:.c=.o))

CC		=	gcc -fcommon

CFLAGS	=	-Wall -Werror -Wextra -g3

$(NAME): .printing_obj $(OBJS) .clear libft.a parser.a
		@$(CC) $(CFLAGS) $(OBJS) libft.a parser -I$(INCLUDES) -lreadline -o $(NAME)
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
		@mv src/parser/parser parser


all:	$(NAME)

clean:
		@make clean -C src/parser -s
		@rm -f $(OBJS)

fclean: clean
		@make fclean -C src/parser -s
		@make fclean -C libft -s
		@rm -f $(NAME)

re:		fclean all

.PHONY: all re clean fclean libft.a parser.a
