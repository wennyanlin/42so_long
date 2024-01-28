NAME = so_long

INCLUDES = so_long.h

SRCS = so_long.c string_utils.c playground_check.c playground_utils.c read_file.c\
		ft_split.c\

OBJS = $(SRCS:.c=.o)

COMPILER = gcc

CFLAGS = -Wall -Werror -Wextra

$(NAME): $(OBJS) $(INCLUDES) Makefile
	$(COMPILER) $(CFLAGS) $(SRCS) -g -fsanitize=address -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS)
		$(MAKE) -C fclean

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
