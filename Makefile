SRCS	=	lib/get_next_line/get_next_line.c \
			lib/get_next_line/get_next_line_utils.c \
			src/error.c \
			src/lib.c \
			src/main.c \
			src/file/flag.c \
			src/file/map.c \
			src/file/scan.c \
			src/file/check_map.c \
			src/file/init.c

OBJS	=	${SRCS:.c=.o}

NAME	=	cub3D

CC		=	cc
RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror
LIBS	=	-lmlx -lX11 -lXext -lbsd -lm

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS} ${LIBS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re