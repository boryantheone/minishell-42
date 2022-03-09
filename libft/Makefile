# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By:  <>                                        +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/10/14 18:52:19 by                   #+#    #+#             #
#   Updated: 202#   Updated: 2022/03/09 09:40:40 by dronel           ###   ########.fr       #                                                              #
# ************************************************************************** #
NAME = libft.a

FUNC = ft_isalpha.c ft_isdigit.c  ft_isascii.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
		 ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strncmp.c \
		 ft_toupper.c ft_tolower.c ft_strrchr.c ft_memchr.c ft_memcmp.c \
		  ft_atoi.c ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c \
		   ft_split.c ft_strjoin.c ft_itoa.c ft_strmapi.c \
		  ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		  ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c

OBJS	= ${FUNC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

HEAD = libft.h

RM = rm -f

AR		= ar rc

LIB		= ranlib

.PHONY: all clean fclean re

all: ${NAME}

.c.o:
			gcc $(CFLAGS) -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}	:	${OBJS} ${HEAD}
			${AR} ${NAME} ${OBJS}
			${LIB} ${NAME}

clean :
			${RM} ${OBJS}
			${RM} ${BONUS_OBJS}

fclean :	clean
			${RM} ${NAME}

#bonus :	${NAME} ${BONUS_FUNC} ${HEAD}
#		gcc ${CFLAGS} -c ${BONUS_FUNC}
#		${AR} ${NAME} ${BONUS_OBJS}


re	:	fclean all clean bonus

