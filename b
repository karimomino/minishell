#    Created: 2021/12/09 05:43:04 by kamin             #+#    #+#              #
				redirection/redirection.c \
				redirection/redirection_in.c \
				redirection/get_next_line.c \
				redirection/get_next_line_utils.c \
				$(DIR_PARSER)free.c $(DIR_PARSER)get_quotes.c \
				$(DIR_PARSER)redir_node.c $(DIR_PARSER)redirections.c \
OBJS		=	$(addprefix $(DIR_S),$(SRC:.c=.o))
# prefix		=	/usr/local/Cellar/readline/8.1
prefix		=	/opt/homebrew/Cellar/readline/8.1.2
exec_prefix	=	${prefix}
libdir		=	${exec_prefix}/lib
includedir	=	${prefix}/include
LDFLAGS 	=	-lreadline -L /usr/local/Cellar/readline/8.1/lib
LDFLAGS 	=	-lreadline -L${libdir}
re:		fclean all
.PHONY: all re clean fclean libft.a parser
