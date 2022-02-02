NAME := miniRT
HEADERFILES := 	includes/miniRT.h \
				includes/parsing.h \
				includes/error_handler.h \
				includes/cleanup.h \
				includes/vector.h \
				includes/color.h
SRCS := srcs/main.c \
		srcs/parsing.c \
		srcs/parse_objects.c \
		srcs/error_handler.c \
		srcs/cleanup.c \
		srcs/raytracing.c \
		srcs/intersect.c \
		srcs/vector.c \
		srcs/color.c

FLAGS := -Wall -Wextra -Werror
OBJFILES := $(SRCS:srcs/%.c=obj/%.o)
LIBFT := libft/
MLX := mlx/

all: $(NAME)

$(NAME): $(OBJFILES)
	@make -C $(LIBFT)
	@make -C $(MLX)
	cp $(MLX)libmlx.dylib .
	gcc -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@ $^

obj/%.o: srcs/%.c $(HEADERFILES)
	@mkdir -p $(dir $@)
	gcc -Imlx -c $(FLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRCS) $(HEADERFILES)

.PHONY: all clean fclean re norm