# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/12 14:53:35 by ommohame          #+#    #+#              #
#    Updated: 2022/06/12 15:31:02 by ommohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lexar

SRCS	=	./srcs/lexar.c \

SRCS_D	=	./debug/print_list.c \

FT_PRINT_F	 =		./ft_printf/libftprintf.a

FT_PF_PATH	 =		./ft_printf

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

AR		=	ar rcs

RM		=	rm -rf

OBJS 	=	$(SRCS:.c=.o)

OBJS_D 	=	$(SRCS_D:.c=.o)

$(NAME)	:	$(OBJS) $(OBJS_D)
			make -C $(FT_PF_PATH)
			$(CC) $(CFLAGS) $(OBJS) $(FT_PRINT_F) $(OBJS_D) -o $(NAME)

all		:	$(NAME)

clean	:
			make clean -C $(FT_PF_PATH)
			$(RM) $(OBJS) $(OBJS_D)

fclean	:	clean
			make fclean -C $(FT_PF_PATH)
			$(RM) $(NAME)

re		:	fclean all