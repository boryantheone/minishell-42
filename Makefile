NAME	=	minishell

LIBFT	=	./libft/libft.a

CFLAGS	=	-Wall -Werror -Wextra

SRCS	=	main.c

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