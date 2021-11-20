# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/13 01:33:32 by abenaiss          #+#    #+#              #
#    Updated: 2021/11/13 09:48:01 by abenaiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC_DIR =./inc/
SRC_DIR =./src/
OBJ_DIR =./obj/

FILES_NAME = clean_forks.c\
			init_env.c\
			life_cycle.c\
			main.c\
			msleep.c\
			my_atoi.c\
			philo_action.c\
			philo_forks.c\
			pick_forks.c\
			print_message.c\
			time_management.c
HEADER_NAME = philo.h\

OBJS = $(addprefix $(OBJ_DIR), $(FILES_NAME:.c=.o))
SRCS = $(addprefix $(SRC_DIR), $(FILES_NAME))
HDRS = $(addprefix $(INC_DIR), $(HEADER_NAME))

all: $(NAME)
$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $@
$(OBJS) : $(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HDRS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
clean:
	@rm -rf $(OBJ_DIR)
fclean: clean
	@rm -rf $(NAME)
re: fclean all