# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 15:08:25 by wlin              #+#    #+#              #
#    Updated: 2023/10/07 17:01:20 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INCLUDES = ft_printf.h

SRCS = ft_printf.c ft_put_digit.c ft_put_chars.c

OBJS = $(SRCS:.c=.o)

COMPILER = cc

FLAGS = -Wall -Werror -Wextra

%.o: %.c Makefile ${INCLUDES}
	$(COMPILER) $(FLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(INCLUDES) Makefile
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)
re:		fclean all

.PHONY: all clean fclean re
