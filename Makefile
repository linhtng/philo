# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2022/11/22 15:30:31 by thuynguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast
DEBUG = -fsanitize=address -g
SRC = philo_main.c \
	philo_check_input.c \
	philo_init.c \
	philo_utils.c \
	philo_time.c  \
	philo_ending.c \
	philo_action.c \

SRCFD = src/
OBJSFD = objs/
SRCS	= $(addprefix $(SRCFD), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJSFD),$(OBJ))

HEADER_PATH = -I ./include

all: $(NAME)

$(OBJSFD)%.o: $(SRCFD)%.c
	@mkdir -p $(OBJSFD)
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@ $(HEADER_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

clean:
	rm -rf $(OBJSFD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
