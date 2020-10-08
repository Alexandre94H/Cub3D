SRCS	=	libraries/get_next_line/get_next_line.c \
			libraries/get_next_line/get_next_line_utils.c \
			sources/error.c \
			sources/library.c \
			sources/file/flag.c \
			sources/file/map.c \
			sources/file/scan.c \
			sources/file/check_map.c \
			sources/file/init.c \
			sources/player/init.c \
			sources/mlx/end.c \
			sources/mlx/bitmap.c \
			sources/mlx/keys/w.c \
			sources/mlx/keys/s.c \
			sources/mlx/keys/a.c \
			sources/mlx/keys/d.c \
			sources/mlx/keys/up.c \
			sources/mlx/keys/down.c \
			sources/mlx/keys/left.c \
			sources/mlx/keys/right.c \
			sources/mlx/keys/f2.c \
			sources/mlx/keys/esc.c \
			sources/mlx/key.c \
			sources/mlx/update.c \
			sources/mlx/init.c \
			sources/main.c

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