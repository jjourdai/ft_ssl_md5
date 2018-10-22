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

SRC_NAME =	main.c \
			md5.c \
			sha256.c \
			display_hash.c \
			exec_command.c \
			base64_encode.c \
			base64_decode.c \
			handle_input_function_flag.c \
			handle_input_hash_function.c \
			handle_input_crypto_function.c \
			param.c \
			des.c \
			keys.c \
			des_encode.c \
			des_decode.c \
			des3.c \
			salt_and_corrupt.c \
			core_des.c \
			error_msg.c \
			des_key_generator.c \
			des3_key_generator.c \


OBJ_PATH = ./.obj/

CPPFLAGS = -Iinclude -I ./libft/include -std=c89

LDFLAGS = -Llibft

LDLIBS = -lft

NAME = ft_ssl

CC = gcc

# CFLAGS = -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer
CFLAGS = -Wall -Wextra -Werror

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
