NAME = so_long

INCLUDES = ./so_long.h \
			./mlx/mlx.h \
			./ft_printf/ft_printf.h

LIB = -Lmlx -lmlx -Lft_printf -lftprintf -framework OpenGL -framework AppKit

SRCS = so_long.c utils_string.c check_game.c read_map.c\
		ft_split.c backend_game.c frontend_game.c frontend_draw.c check_map.c\
		handle_errors.c utils_array.c\

OBJS = $(SRCS:.c=.o)

COMPILER = gcc

CFLAGS = -Wall -Werror -Wextra

%.o: %.
	$(COMPILER) $(CFLAGS) -Imlx -Iftprintf -c $< -o ${<:.c=.o}

$(NAME): $(OBJS) $(INCLUDES) Makefile
		@make -C ./mlx all
		@make -C ./ft_printf all
		@$(COMPILER) $(SRCS) $(LIB) mlx/libmlx.a ft_printf/libftprintf.a -g -fsanitize=address -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS)
		$(MAKE) -C ./mlx clean
		$(MAKE) -C ./ft_printf clean


fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re

#-g -fsanitize=address
#leaks --atExit -- ./so_long maps/map1.ber
#mlx/libmlx.a -E
