NAME = so_long

INCLUDES = ./so_long.h \
			./mlx/mlx.h

LIB = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS = so_long.c string_utils.c playground_check.c playground_utils.c read_file.c\
		ft_split.c frontend.c\

OBJS = $(SRCS:.c=.o)

COMPILER = gcc

CFLAGS = -Wall -Werror -Wextra

%.o: %.c
	$(COMPILER) $(CFLAGS) -Imlx -c $< -o ${<:.c=.o}

$(NAME): $(OBJS) $(INCLUDES) Makefile
		@make -C ./mlx all
		@$(COMPILER) $(SRCS) $(LIB) mlx/libmlx.a -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS)
		$(MAKE) -C ./mlx clean

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
