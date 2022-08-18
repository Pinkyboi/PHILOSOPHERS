# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 21:54:57 by abenaiss          #+#    #+#              #
#    Updated: 2022/08/18 18:20:23 by abenaiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC_DIR =./inc/
SRC_DIR =./src/
OBJ_DIR =./obj/

FILES_NAME =	clean_forks.c\
				init_env.c\
				life_cycle.c\
				main.c\
				msleep.c\
				my_atoi.c\
				philo_action.c\
				philo_forks.c\
				pick_forks.c\
				print_message.c\
				error_handle.c\
				time_management.c

SRCS = $(addprefix $(SRC_DIR), $(FILES_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(FILES_NAME:.c=.o))

DIR_CREATE = @mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(HDRS) $(OBJS)
	@$(CC) $(OBJS) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(DIR_CREATE)
	@$(CC) $(CFLAGS) -c $^ -o $@ -I $(INC_DIR)

clean:
	@rm -rf $(OBJ_DIR)
fclean: clean
	@rm -rf $(NAME)
re: fclean all