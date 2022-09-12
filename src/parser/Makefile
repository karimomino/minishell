# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/12 14:53:35 by ommohame          #+#    #+#              #
#    Updated: 2022/09/12 18:32:20 by ommohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=		parser.a

SRCS		=		./parser.c \
					../utils/print_list.c \
					../utils/ft_strlenx2.c \
					../utils/ft_split_sc.c \
					../utils/ft_split_rd.c \
					../utils/ft_split_q.c \
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

LIBFT_SRC	=		../../libft/ft_memset.c ../../libft/ft_bzero.c ../../libft/ft_memcpy.c ../../libft/ft_memmove.c ../../libft/ft_memchr.c ../../libft/ft_memcmp.c ../../libft/ft_strlen.c ../../libft/ft_isalpha.c ../../libft/ft_isdigit.c ../../libft/ft_isalnum.c \
				../../libft/ft_isascii.c ../../libft/ft_isprint.c ../../libft/ft_toupper.c ../../libft/ft_tolower.c ../../libft/ft_strchr.c ../../libft/ft_strrchr.c ../../libft/ft_strncmp.c ../../libft/ft_strlcpy.c ../../libft/ft_strlcat.c ../../libft/alpha_strjoin.c ../../libft/ft_strnstr.c \
				../../libft/ft_atoi.c ../../libft/ft_calloc.c ../../libft/ft_strdup.c ../../libft/ft_substr.c ../../libft/ft_strjoin.c ../../libft/ft_strtrim.c ../../libft/ft_split.c ../../libft/ft_itoa.c ../../libft/ft_strmapi.c ../../libft/ft_putchar_fd.c ../../libft/ft_putstr_fd.c \
				../../libft/ft_putendl_fd.c ../../libft/ft_putnbr_fd.c ../../libft/ft_striteri.c ../../libft/ft_checkdup.c ../../libft/ft_strcmp.c ../../libft/ft_split_wc.c ../../libft/ft_isnum.c ../../libft/ft_isint.c \
				../../libft/ft_printf/ft_printf.c	\
				../../libft/ft_printf/ft_puthex.c \
				../../libft/ft_printf/ft_putnums.c \
				../../libft/ft_printf/ft_putchars.c \

RM			=		rm -rf

OBJS 		=		$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -g3

LIBFT_OBJS 		=		$(LIBFT_SRC:.c=.o)

$(NAME)	:	$(OBJS)
			@ar -rcs $(NAME) $(OBJS) $(LIBFT_OBJS)

all		:	$(NAME)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) ../../$(NAME)

re		:	fclean all
