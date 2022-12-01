# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmonney <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 23:49:58 by rmonney           #+#    #+#              #
#    Updated: 2022/11/29 23:50:00 by rmonney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= srcs/main.cpp\


OBJS		= ${SRCS:.cpp=.o}

RM			= rm -f

NAME		= test

FLAGS		= -Wall -Wextra -Werror -std=c++98

CC			= g++-11

.cpp.o:
			${CC} ${FLAGS} -c $< -o ${<:.cpp=.o}

${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

good:		re clean

.PHONY:		all clean fclean re good
