# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 05:43:04 by kamin             #+#    #+#              #
#    Updated: 2022/09/14 14:23:42 by ommohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

INCLUDES	=	./includes

DIR_S		=	./src/
DIR_PARSER	=	parser/
DIR_UTILS	=	utils/

SRC			=	builtins/env.c \
				builtins/echo.c \
				builtins/pwd.c \
				builtins/cd.c \
				builtins/exit.c \
				builtins/utils.c \
				environment/environment.c \
				execution/exec.c \
				execution/utils.c \
				main.c \
				history/history.c \
				history/history_cmd.c \
				redirection/redirection.c \
				redirection/redirection_in.c \
				redirection/get_next_line.c \
				redirection/get_next_line_utils.c \
				signals/signals.c \
				pipe/pipe.c \
				$(DIR_PARSER)cmd_node.c $(DIR_PARSER)cmp_cmd.c \
				$(DIR_PARSER)commands.c $(DIR_PARSER)expansion.c \
				$(DIR_PARSER)free.c $(DIR_PARSER)get_quotes.c \
				$(DIR_PARSER)last_cmd.c $(DIR_PARSER)parser.c \
				$(DIR_PARSER)redir_node.c $(DIR_PARSER)redirections.c \
				$(DIR_PARSER)split_line.c $(DIR_PARSER)fake_string.c\
				$(DIR_UTILS)squeeze.c $(DIR_UTILS)ft_split_rd.c \
				$(DIR_UTILS)ft_split_sc.c $(DIR_UTILS)ft_strlenx2.c \
				$(DIR_UTILS)pipes.c $(DIR_UTILS)print_list.c \
				$(DIR_UTILS)ft_split_q.c \

OBJS		=	$(addprefix $(DIR_S),$(SRC:.c=.o))

prefix		=	/opt/homebrew/Cellar/readline/8.1.2
# prefix		=	/usr/local/Cellar/readline/8.1

exec_prefix	=	${prefix}

libdir		=	${exec_prefix}/lib

includedir	=	${prefix}/include

LDFLAGS 	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib

CFLAGS		=	-Wall -Wextra -Werror -g3 -I${includedir}

LDFLAGS 	=	-lreadline -L${libdir}

CC		=	gcc -fcommon

all:	$(NAME)

# $(NAME): .printing_obj libft.a $(OBJS) $(PARSER_OBJS) .clear

$(NAME): .printing_obj $(OBJS) libft.a
		@$(CC) $(CFLAGS) $(OBJS) $(UTILS_OBJS) $(PARSER_OBJS) ./libft.a -I$(INCLUDES) $(LDFLAGS) -o $(NAME)
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
		@mv src/parser/parser.a parser.a


all:	$(NAME)

clean:
		@make clean -C src/parser -s
		@rm -f $(OBJS)

fclean: clean
		@$(MAKE) fclean -C libft -s
		@make fclean -C src/parser -s
		@rm -f $(NAME)
		@if [ -f src/history/.history ]; then rm src/history/.history; fi

re:		fclean all

.PHONY: all re clean fclean libft.a parser
