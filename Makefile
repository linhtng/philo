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
CFLAGS = -Wall -Wextra -Werror -g3
SRC = src/philo_main.c \
	src/philo_check_input.c \
	src/philo_init.c \
	src/philo_utils.c \
	src/philo_time.c  \
	src/philo_ending.c \
	src/philo_action.c \
OBJSFD 	= objs
OBJS 	= $(addprefix $(OBJSFD)/, $(notdir $(SRC:.c=.o)))
HEADERS = include/philo.h
HEADER_PATH = ./include

all: $(NAME)

$(OBJSFD):
	mkdir $@

$(OBJSFD)/%.o: src/%.c | $(OBJSFD)
	cc $(CFLAGS) -I $(HEADER_PATH) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS) | $(OBJSFD)
	cc $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJSFD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
