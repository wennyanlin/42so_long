NAME = so.long

INCLUDES = so.long.h

SRCS = so.long.c\

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
