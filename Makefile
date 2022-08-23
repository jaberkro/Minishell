# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/19 13:48:23 by jaberkro      #+#    #+#                  #
#    Updated: 2022/08/23 11:14:21 by bsomers       ########   odam.nl          #
#																			   #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
INC = -I ./libft -I ./include -I/Users/$(USER)/.brew/opt/readline/include

LIBFT_DIR = libft/
LIBFT = libft/libft.a

SRC_DIR = src
BUILD_DIR = obj

SRC = 	global/get_env.c \
		global/init.c \
		global/set_env.c \
		global/unset_env.c \
		executer/executer.c \
		executer/fd_dup2.c \
		protected.c \
		main.c \
		error.c \
		path.c \
		signals.c \
		parse/parse.c \
		parse/dollar.c \
		parse/get_next_line.c \
		parse/split_pipes.c \
		parse/heredoc.c \
		parse/heredoc_read.c \
		parse/utils.c \
		parse/utils_checks.c \
		parse/clean_and_free.c \
		parse/init_and_finish.c \
		parse/quotes.c \
		parse/write_parts.c \
		parse/write_parts_utils.c \
		parse/set_terminal.c \
		builtin/builtin.c \
		builtin/cd.c \
		builtin/echo.c \
		builtin/env.c \
		builtin/exit.c \
		builtin/export.c \
		builtin/pwd.c \
		builtin/unset.c

OBJ := $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
SRC := $(addprefix $(SRC_DIR)/, $(SRC))

# COLORS
PINK	= \x1b[35m
BLUE	= \x1b[34m
YELLOW	= \x1b[33m
GREEN	= \x1b[32m
RED		= \x1b[31m
CYAN	= \x1b[36m
RESET	= \x1b[0m

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	CC $(FLAGS) $(INC) -c $^ -o $@

$(NAME): $(LIBFT) $(OBJ)
	cp $(LIBFT) ./$(NAME)
	CC $(OBJ) $(LDFLAGS) $(LIBFT) $(INC) -o $(NAME)
	@echo "DONE COMPILING $(PINK)MI$(RED)NI$(YELLOW)SH$(GREEN)EL$(CYAN)L!$(RESET)"

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

run: $(NAME)
	@./$(NAME)

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "DONE CLEANING $(PINK)MI$(RED)NI$(YELLOW)SH$(GREEN)EL$(CYAN)L!$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "DONE FANCY CLEANING $(PINK)MI$(RED)NI$(YELLOW)SH$(GREEN)EL$(CYAN)L!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
