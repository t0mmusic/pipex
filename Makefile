# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 09:35:29 by jbrown            #+#    #+#              #
#    Updated: 2022/06/02 09:47:22 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDES = -Iincludes -Iprintf/headers

PRINTF = printf/libftprintf.a

SRCS = srcs/*.c

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS) $(PRINTF) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all