# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 01:17:13 by huvu              #+#    #+#              #
#    Updated: 2025/04/09 11:19:15 by huvu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
CC = cc
CFLAGS= -Wall -Wextra -Werror

# Files
NAME = bsq
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
	$(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Link object files into executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Compile .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	rm -f $(OBJ)

# Remove object files + executable
fclean: clean
	rm -f $(NAME)
re: fclean all
	@echo "Rebuild done"

norm:
	@echo "Norminette, please say OK!"
	@norminette $(SRC_DIR)/*/*.c $(SRC_DIR)/*/*.h
.PHONY: all clean fclean%
