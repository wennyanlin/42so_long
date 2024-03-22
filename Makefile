NAME = so_long

CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD
CPPFLAGS = -Iinclude -I$(SRC_DIR)/mlx -I$(SRC_DIR)/ft_printf
LDFLAGS = -L$(SRC_DIR)/mlx -L$(SRC_DIR)/ft_printf
LDLIBS := -framework OpenGL -framework AppKit -lmlx -lftprintf
SRC_DIR		:=	src

SRC_FILES	:=	$(SRC_DIR)/so_long.c \
				$(SRC_DIR)/utils_string.c \
				$(SRC_DIR)/check_game.c \
				$(SRC_DIR)/read_map.c \
				$(SRC_DIR)/ft_split.c \
				$(SRC_DIR)/backend_game.c \
				$(SRC_DIR)/frontend_game.c \
				$(SRC_DIR)/frontend_draw.c \
				$(SRC_DIR)/check_map.c \
				$(SRC_DIR)/handle_errors.c \
				$(SRC_DIR)/utils_array.c

OBJ_FILES	=	$(SRC_FILES:.c=.o)
DEP_FILES	=	$(SRC_FILES:.c=.d)

all: MLX FT_PRINTF $(NAME)

$(NAME): Makefile $(OBJ_FILES) src/so_long.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ_FILES) -o $@

clean:
		rm -f $(OBJ_FILES) $(DEP_FILES)
		make -C $(SRC_DIR)/mlx clean
		make -C $(SRC_DIR)/ft_printf clean

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re MLX FT_PRINTF

MLX:
	make -C $(SRC_DIR)/mlx --no-print-directory

FT_PRINTF:
	make -C $(SRC_DIR)/ft_printf --no-print-directory

-include $(DEP_FILES)
#-g -fsanitize=address
#leaks --atExit -- ./so_long maps/map1.ber
#mlx/libmlx.a -E