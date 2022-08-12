# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/19 13:48:23 by jaberkro      #+#    #+#                  #
#    Updated: 2022/08/12 16:32:34 by jaberkro      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline -fsanitize=address -g3
INC = -I ./libft -I ./include -I/Users/$(USER)/.brew/opt/readline/include

LIBFT_DIR = libft/
LIBFT = libft/libft.a

SRC_DIR = src
BUILD_DIR = obj

SRC = 	$(SRC_DIR)/init_global.c \
		$(SRC_DIR)/executer.c \
		$(SRC_DIR)/protected.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/path.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/parse_split_pipes.c \
		$(SRC_DIR)/parse_heredoc.c \
		$(SRC_DIR)/parse_utils.c \
		$(SRC_DIR)/builtin.c \
		$(SRC_DIR)/dollar.c \
		$(SRC_DIR)/builtin_export.c \
		$(SRC_DIR)/env.c \
		$(SRC_DIR)/exit.c

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
	$(CC) $(FLAGS) $(INC) -c $^ -o $@

$(NAME): $(LIBFT) $(OBJ)
	cp $(LIBFT) ./$(NAME)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBFT) $(INC) -o $(NAME)
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