# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/12 14:53:35 by ommohame          #+#    #+#              #
#    Updated: 2022/06/17 03:17:20 by ommohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		parser

SRCS		=		./srcs/parser.c \
					./srcs/utils/print_list.c \
					./srcs/utils/ft_strlenx2.c \
					./srcs/utils/ft_splitq.c \
					./srcs/linked_list/cmd_node.c \
					./srcs/cmp_cmd.c \
					./srcs/get_quotes.c \

LIBFT_PATH	=		./Libft

LIBFT		=		./Libft/libft.a

FT_PF_PATH	=		./ft_printf

FT_PRINT_F	=		./ft_printf/libftprintf.a

CC			=		gcc

CFLAGS		=		-Wall -Werror -Wextra -g

AR			=		ar rcs

RM			=		rm -rf

OBJS 		=		$(SRCS:.c=.o)

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