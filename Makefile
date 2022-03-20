
NAME	=	minishell

LIBFT	=	./libft/libft.a

CFLAGS	=	 -I ${HEADER}

HEADER	=	minishell.h

#  -Wall -Werror -Wextra

SRCS	=	parser/main.c parser/preparser.c parser/parser.c parser/parser_quotes.c\
			parser/make_envp.c parser/parser_redirect.c parser/parser_fds.c parser/ft_parser_utils.c\
 			run_commands/handler_pipe.c build_in/build_in.c run_commands/execute.c \
 			run_commands/handler_cmd.c

OBJS	=	${SRCS:.c=.o}

CC		=	cc

%.o	:	%.c
		${CC} ${CFLAGS} $< -c -o $@

${NAME}	:	${OBJS} ${LIBFT} 
			${CC} ${CFLAGS} ${OBJS} -lreadline \
 			-L${HOME}/.brew/Cellar/readline/8.1.2/lib/ \
 			-I${HOME}/.brew/Cellar/readline/8.1.2/include/ \
 			-L./libft -lft -o ${NAME}

.PHONY	:	all re clean fclean libft

all		:	${NAME}

${LIBFT} : libft ;

libft	:
			${MAKE} -C ./libft

clean	:
			rm -rf ${OBJS}
			${MAKE} -C ./libft clean

fclean	:	clean
			rm -rf ${NAME}
			${MAKE} -C ./libft fclean

re		: fclean all

ch_leaks :
			leaks -atExit -- ./${NAME}