# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamin <kamin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 22:31:49 by kamin             #+#    #+#              #
#    Updated: 2022/09/11 20:20:40 by kamin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

SRCS			=	ft_bzero.c ft_strlen.c \
					ft_tolower.c \
					ft_isalpha.c ft_isdigit.c \
					ft_strchr.c ft_strncmp.c \
					ft_atoi.c ft_calloc.c \
					ft_strdup.c ft_substr.c \
					ft_strjoin.c ft_split.c \
					ft_itoa.c alpha_strjoin.c \
					ft_putchar_fd.c ft_strnstr.c \
					ft_putstr_fd.c ft_strcmp.c \
					ft_printf/ft_printf.c	\
					ft_printf/ft_puthex.c \
					ft_printf/ft_putnums.c \
					ft_printf/ft_putchars.c \
					ft_memset.c ft_strtrim.c \
					ft_putnbr_fd.c ft_strlcpy.c \

OBJS			= $(SRCS:.c=.o)

CC				= gcc -c -g3
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.


all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
