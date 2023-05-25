# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niboukha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 14:21:51 by niboukha          #+#    #+#              #
#    Updated: 2023/05/24 18:19:02 by niboukha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread -g3

CC = cc

SRC = philo_bonus.c ft_atoi.c util_bonus.c

OBJ = $(SRC:.c=.o)

all :$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: all re clean fclean