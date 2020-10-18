SOURCES				=	libraries/get_next_line/get_next_line.c \
						libraries/get_next_line/get_next_line_utils.c \
						sources/error.c \
						sources/library_1.c \
						sources/library_2.c \
						sources/library_3.c \
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
						sources/mlx/keys/left.c \
						sources/mlx/keys/right.c \
						sources/mlx/keys/f2.c \
						sources/mlx/keys/esc.c \
						sources/mlx/key.c \
						sources/mlx/update/floor.c \
						sources/mlx/update/wall.c \
						sources/mlx/update/sprite.c \
						sources/mlx/update/update.c \
						sources/mlx/texture.c \
						sources/mlx/init.c \
						sources/main.c
SOURCES_BONUS		=	bonus/mlx/keys/up.c \
						bonus/mlx/keys/down.c \
						bonus/mlx/keys/alt.c \
						bonus/mlx/keys/shift.c

OBJECTS				=	${SOURCES:.c=.o}
OBJECTS_BONUS		=	${SOURCES_BONUS:.c=.o}

NAME				=	cub3D

COMPILE				=	cc
REMOVE				=	rm -f

BONUS				=	0
COMPILATION_FLAGS	=	-Wall -Wextra -Werror
LIBRARIES			=	-lmlx -lX11 -lXext -lbsd -lm

.c.o:
	${COMPILE} ${COMPILATION_FLAGS} -DBONUS=${BONUS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
	${COMPILE} -o ${NAME} ${OBJECTS} ${LIBRARIES}

all: ${NAME}

clean:
	${REMOVE} ${OBJECTS} ${OBJECTS_BONUS}

fclean: clean
	${REMOVE} ${NAME}

re: fclean all

bonus_init:
	${eval BONUS = 1}
	${eval OBJECTS += ${OBJECTS_BONUS}}

bonus: bonus_init ${OBJECTS_BONUS} all

.PHONY: all clean fclean re bonus_init bonus