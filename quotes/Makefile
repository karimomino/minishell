# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 18:38:50 by ommohame          #+#    #+#              #
#    Updated: 2022/07/09 18:58:53 by ommohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		quotes

SRCS		=		./srcs/quotes.c \

OBJS		=		$(SRCS:.c=.o)

LIBFT_PATH	=		./Libft

LIBFT		=		./Libft/libft.a

FT_PF_PATH	=		./ft_printf

FT_PRINT_F	=		./ft_printf/libftprintf.a

CC			=		gcc

CFLAGS		=		-Wall -Werror -Wextra -g3

RM			=		rm -rf

$(NAME)	:	$(OBJS)
			make -C $(LIBFT_PATH)
			make -C $(FT_PF_PATH)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINT_F) -o $(NAME)

all		:	$(NAME)

clean	:
			make clean -C $(LIBFT_PATH)
			make clean -C $(FT_PF_PATH)
			$(RM) $(OBJS)

fclean	:	clean
			make fclean -C $(LIBFT_PATH)
			make fclean -C $(FT_PF_PATH)
			$(RM) $(NAME)

re		:	fclean all