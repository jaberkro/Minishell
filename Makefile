# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jaberkro <jaberkro@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/19 13:48:23 by jaberkro      #+#    #+#                  #
#    Updated: 2022/07/28 17:05:19 by bsomers       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline -g3 -fsanitize=address
INC = -I ./libft -I ./include -I/Users/$(USER)/.brew/opt/readline/include

LIBFT_DIR = libft/
LIBFT = libft/libft.a

SRC_DIR = src
BUILD_DIR = obj

SRC = 	$(SRC_DIR)/global.c \
		$(SRC_DIR)/executer.c \
		$(SRC_DIR)/protected.c \
		$(SRC_DIR)/path.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/parse_split_pipes.c \
		$(SRC_DIR)/parse_utils.c \
		$(SRC_DIR)/builtin.c
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

$(NAME): $(LIBFT) $(OBJ) 
	cp $(LIBFT) ./$(NAME)
	CC $(LDFLAGS) $(OBJ) $(LIBFT) $(INC) -o $(NAME)
	@echo "$(RED)Done $(GREEN)COM$(YELLOW)PI$(BLUE)LING $(PINK)MINISHELL$(RESET):)"

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

run: $(NAME)
	@./$(NAME)

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)Done $(GREEN)CLEANING$(YELLOW) MINISHELL$(PINK) :)$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)Done $(GREEN)FANCY CLEANING$(YELLOW) MINISHELL$(PINK) :)$(RESET)"

re: fclean all

.PHONY: all clean fclean re