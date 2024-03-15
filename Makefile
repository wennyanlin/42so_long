NAME = so_long

INCLUDES = ./so_long.h \
			./mlx/mlx.h

LIB = -Lmlx -lmlx -Lft_printf -lftprintf -framework OpenGL -framework AppKit

SRCS = so_long.c string_utils.c playground_check.c read_map_file.c\
		ft_split.c frontend.c map_check.c\

OBJS = $(SRCS:.c=.o)

COMPILER = gcc

CFLAGS = -Wall -Werror -Wextra

%.o: %.c
	$(COMPILER) $(CFLAGS) -Imlx -c $< -o ${<:.c=.o}

$(NAME): $(OBJS) $(INCLUDES) Makefile
		@make -C ./mlx all
		@$(COMPILER) $(SRCS) $(LIB) mlx/libmlx.a -g -fsanitize=address -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS)
		$(MAKE) -C ./mlx clean

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re

#-g -fsanitize=address
#leaks --atExit -- ./so_long maps/map1.ber
#mlx/libmlx.a -E
