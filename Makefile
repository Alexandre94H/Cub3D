# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/18 23:00:35 by ahallain          #+#    #+#              #
#    Updated: 2020/05/06 20:13:16 by ahallain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	main/cub3d.c \
			main/utils.c \
			parse/load.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			parse/edit.c \
			parse/check.c \
			runtime/game.c \
			runtime/event.c \
			runtime/update.c \
			runtime/raycaster.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Werror -Wextra -Wall

LIBS	=	-lmlx -lX11 -lXext -lm

.c.o:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:
	@echo "\033[1;33mCompiling ${NAME}...\033[0m"
	make ${OBJS}
	gcc ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}
	@echo "\033[1;32mDone\033[0m"

all: ${NAME}

offline_clean:
	rm -rf ${OBJS}

clean:
	@echo "\033[1;31mRemoving compilation file...\033[0m"
	@make offline_clean
	@echo "\033[1;32mDone\033[0m"

fclean:
	@echo "\033[1;31mRemoving compilation file...\033[0m"
	@make offline_clean
	rm -rf ${NAME}
	@echo "\033[1;32mDone\033[0m"

re: fclean all

.PHONY: all offline_clean clean fclean re