# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/24 17:00:59 by llebugle          #+#    #+#              #
#    Updated: 2024/11/30 17:42:49 by llebugle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

# -----------------------------------Colors------------------------------------

RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[1;33m
BLUE	=\033[0;34m
ORANGE	=\033[38;2;255;165;0m
RESET	=\033[0m

CC = cc
CFLAGS = -Wall -Werror -Wextra

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

SRCS = main.c \
		utils.c \
		path.c
		
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -s -C libft
	@echo "$(GREEN)  ✧ Compiling... $(RESET)"
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) generated $(RESET)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(INC) -c $< -o $@
#	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@make -s -C libft

fclean: clean
	@rm -rf $(NAME) $(CHECKER)
	@make -s fclean -C libft
	@echo "$(BLUE) $(NAME) removed $(RESET)"

clean:
	@rm -rf  $(OBJS_DIR) $(OBJS_CHECKER_DIR)
	@make -s clean -C libft
	@echo "$(BLUE) Object files removed $(RESET)"

re : fclean all

.PHONY: all clean fclean re bonus