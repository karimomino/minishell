# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamin <kamin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/12 14:53:35 by ommohame          #+#    #+#              #
#    Updated: 2022/09/11 20:15:58 by kamin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=		parser.a

SRCS		=		./parser.c \
					../utils/print_list.c \
					../utils/ft_strlenx2.c \
					../utils/ft_split_sc.c \
					../utils/ft_split_rd.c \
					./cmd_node.c \
					./expansion.c \
					./redir_node.c \
					./last_cmd.c \
					./cmp_cmd.c \
					./get_quotes.c \
					./free.c \
					./redirections.c \
					./commands.c \
					./split_line.c \
					../utils/squeeze.c \
					../utils/pipes.c \

RM			=		rm -rf

OBJS 		=		$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g3

$(NAME)	:	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

all		:	$(NAME)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) ../../$(NAME)

re		:	fclean all
