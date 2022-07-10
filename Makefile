# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamin <kamin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 05:43:04 by kamin             #+#    #+#              #
#    Updated: 2022/07/10 14:56:47 by kamin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

INCLUDES	=	./includes

DIR_S		=	./src/

SRC		=	builtins/env.c \
			builtins/echo.c \
			builtins/pwd.c \
			execution/exec.c \

OBJS	=	$(addprefix $(DIR_S),$(SRC:.c=.o))

CC		=	gcc -fcommon

CFLAGS	=	-Wall -Werror -Wextra -g3

$(NAME): $(OBJS)
		@$(MAKE) -C libft
		@echo "Make libft successful"
		@mv libft/libft.a libft.a
		$(CC) $(CFLAGS) $(addprefix $(DIR_S),$(SRC)) libft.a -I$(INCLUDES) -o $(NAME)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)
		rm -f libft.a
		rm -f libft/*.o
		rm -f libft/libft.a

re:		fclean all
