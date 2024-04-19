NAME	:= cub3D
CFLAGS	:= -Wall -Wextra -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBGNL	:= ./lib/get_next_line
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBGNL)/include -I $(LIBFT)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBGNL)/libgnl.a $(LIBFT)/libft.a
SRCS	:= $(shell find src -type f -name "*.c")
OBJS	:= $(SRCS:src/%.c=obj/%.o)

all: libmlx libgnl libft $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build
	cmake --build $(LIBMLX)/build -j4

libgnl:
	make -C $(LIBGNL)

libft:
	make -C $(LIBFT)

obj/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Linked: $(NAME)"

clean:
	rm -f $(OBJS) && echo "Removed: $(OBJS)"
	rm -rf $(LIBMLX)/build && echo "Removed: $(LIBMLX)/build"
	make -C $(LIBGNL) clean
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME) && echo "Removed: $(NAME)"

re: clean all

.PHONY: all clean fclean re libmlx libgnl libft
.SILENT:
