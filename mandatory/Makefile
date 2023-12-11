# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:39:29 by mvpee             #+#    #+#              #
#    Updated: 2023/12/11 20:51:26 by mvpee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ../libft

SRCS = 	srcs/main.c \
		srcs/utils.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -I$(LIBFT) -Wall -Werror -Wextra

all: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	gcc $(OBJS) -L$(LIBFT) -lft -o $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) input "ls" "wc" output

test: all
	valgrind --leak-check=full ./$(NAME) input "ls" "wc" output

.PHONY: all clean fclean re