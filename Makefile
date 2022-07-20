# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jaberkro <jaberkro@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/19 13:48:23 by jaberkro      #+#    #+#                  #
#    Updated: 2022/07/19 18:37:32 by jaberkro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
INC = -I ./include

SRC_DIR = src
BUILD_DIR = obj

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/executer.c \
		$(SRC_DIR)/protected.c \
		$(SRC_DIR)/libft_utils.c \
		$(SRC_DIR)/libft_ftsplit.c
OBJ = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC:.c=.o))

# COLORS
PINK	= \x1b[35m
BLUE	= \x1b[34m
YELLOW	= \x1b[33m
GREEN	= \x1b[32m
RED		= \x1b[31m
RESET	= \x1b[0m

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	CC $(FLAGS) $(INC) -c $^ -o $@

$(NAME): $(OBJ)
	CC $(FLAGS) $(OBJ) $(INC) -o $(NAME)
	@echo "$(RED)Done $(GREEN)COM$(YELLOW)PI$(BLUE)LING $(PINK)MINISHELL$(RESET):)"

clean:
	rm -rf $(BUILD_DIR)
	@echo "$(RED)Done $(GREEN)CLEANING$(YELLOW) MINISHELL$(PINK) :)$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)Done $(GREEN)FANCY CLEANING$(YELLOW) MINISHELL$(PINK) :)$(RESET)"

re: fclean all

.PHONY: all clean fclean re
