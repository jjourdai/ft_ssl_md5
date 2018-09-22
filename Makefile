# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 13:28:01 by jjourdai          #+#    #+#              #
#*   Updated: 2017/03/06 14:29:20 by jjourdai         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/

SRC_NAME = main.c \
		   md5.c \
		   sha256.c \
		   handle_input_hash_function.c \
			 handle_input_base64.c \
			 display_hash.c \
			 exec_command.c \
			 base64.c \
			 get_hash_function_flag.c \
			 get_base64_function_flag.c \
			param.c

OBJ_PATH = ./.obj/

CPPFLAGS = -Iinclude -I ./libft/include

LDFLAGS = -Llibft

LDLIBS = -lft

NAME = ft_ssl

CC = gcc

#CFLAGS = -Wall -Wextra -g -fsanitize=address
CFLAGS = -Wall -Wextra -g 

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
OBJ_FULL_PATH = $(addprefix $(OBJ_PATH), $(OBJ_SUB_DIR))

.PHONY: all, clean, fclean, re, asm

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft/
	$(CC) $^ -o $(NAME) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -ltermcap

$(OBJ_PATH)%.o: $(SRC_PATH)%.c ./include
	@mkdir $(OBJ_PATH) $(OBJ_FULL_PATH) 2> /dev/null || true
	$(CC) -o $@  $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -fv $(OBJ)
	make clean -C ./libft/
	@rmdir $(OBJ_PATH) $(OBJ_FULL_PATH) 2> dev/null || true

fclean: clean
	make fclean -C ./libft/
	rm -fv $(NAME)

re: fclean all
