# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/25 17:44:49 by j.fox             #+#    #+#              #
#    Updated: 2026/10/12 19:21:25 by jfox             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJECT_DIR ?= ./object_files
SRC_DIR = ./src
INC_DIR = ./include

SRC =	main.c \
		parsing.c \
		forks.c \
		time.c \
		utils.c \
		threads.c \
		sim.c \
		monitor.c \
		cleaning.c

NAME = philo
OBJ = $(SRC:%.c=$(OBJECT_DIR)/%.o)

CC = cc
CFLAGS += -pthread -Wall -Wextra -Werror -g -I$(INC_DIR) -MMD -MP

all: $(NAME) ping_make

# ---------- Build objects ----------
$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(CFLAGS)

# --------- Build minishell ----------
$(NAME): $(TOOLS) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[32m----------The philo executable and object files have been made----------\033[0m"

clean:
	@rm -rf $(OBJECT_DIR)
	@echo "\033[33m------------The philo Object_Files were removed successfully------------\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33m--------------The executable has been removed successfully--------------\033[0m"
	@echo "\033[33m"
	@echo "=============================CLEAN COMPLETE=============================\033[0m"

re: ping_re fclean all

ping_make:
	@echo "\033[32m"
	@echo "=============================MAKE COMPLETE==============================\033[0m"

ping_re:
	@echo "\033[31m"
	@echo "=======================REBUILDING THE EXECUTABLE========================\033[0m"

ping_valgrind:
	@echo "\033[34m"
	@echo "==========================TESTING IN VALGRIND===========================\033[0m"

valgrind: $(NAME) ping_valgrind
	@echo && valgrind --leak-check=full --show-leak-kinds=all ./philo 4 410 200 200 10

.PHONY: all clean fclean re tools ping_make ping_re ping_valgrind valgrind

-include $(OBJ:.o=.d)