# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:39:29 by mvpee             #+#    #+#              #
#    Updated: 2023/12/12 12:53:53 by mvan-pee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = srcs/libft

SRCS = 	srcs/main.c \
		srcs/utils.c \
		srcs/find_path.c

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
	./$(NAME) input "ls -l" "wc -l" output

test: all
	valgrind --leak-check=full ./$(NAME) input "ls" "wc" output

.PHONY: all clean fclean re