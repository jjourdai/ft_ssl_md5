# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 13:28:01 by jjourdai          #+#    #+#              #
#    Updated: 2018/10/19 14:42:30 by jjourdai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/

SRC_NAME = ft_memalloc.c ft_strcat.c ft_strncmp.c \
	   ft_memccpy.c ft_strchr.c ft_strncpy.c \
	   ft_atoi.c ft_memchr.c ft_strclr.c ft_strnequ.c \
	   ft_bzero.c ft_memcmp.c ft_strcmp.c ft_strnew.c \
	   ft_memcpy.c ft_strcpy.c ft_strnstr.c \
	   ft_memdel.c ft_strdel.c ft_strrchr.c \
	   ft_memmove.c ft_strdup.c ft_strsplit.c \
	   ft_memset.c ft_strequ.c ft_strstr.c \
	   ft_putchar.c ft_striter.c ft_strsub.c \
	   ft_itoa.c ft_striteri.c ft_strtrim.c \
	   ft_lstadd.c ft_strjoin.c ft_tolower.c \
	   ft_strlcat.c ft_toupper.c \
	   ft_putnbr.c ft_strlen.c \
	   ft_strmap.c ft_strncat.c \
	   ft_putstr.c ft_strmapi.c \
	   ft_convert_decitooctal.c ft_itoa_base.c \
	   ft_strndup.c ft_itoa_0x.c ft_del.c \
	   ft_int_size.c ft_itoa_ll.c ft_itoa_l.c ft_itoa_ul.c \
	   ft_itoa_ull.c ft_itoa_u.c ft_itoa_base_ll.c ft_itoa_base_uint.c \
	   ft_itoa_ul.c ft_itoa_base_l.c ft_itoa_base_ul.c ft_itoa_base_ull.c \
	   ft_itoa_hh.c ft_itoa_h.c ft_itoa_base_h.c ft_itoa_base_hh.c \
	   ft_strchr_base.c ft_strwlen.c ft_int_size.c \
	   print_bits.c ft_wcrtomb.c ft_itoa_ulong.c ft_itoa_base_uh.c ft_itoa_uh.c \
	   ft_itoa_base_uhh.c ft_itoa_uhh.c \
	   ft_strcut.c get_next_line.c ft_lststrsplit.c \
	   ft_lst_merge.c ft_printf.c ft_repart.c ft_arg.c ft_flag.c \
	   ft_parser.c ft_arg_ptr.c ft_putbuf.c ft_lstatoisplit.c \
	   ft_is_sort.c ft_list_size.c ft_putnbuf.c ft_cpychar.c \
	   ft_count_less.c ft_insertion_sort.c ft_quick_sort.c ft_str_is_only_digit.c \
	   ft_is.c ft_count_char.c ft_split.c ft_atoi_base.c \
	   ft_parser_flag.c ft_lstadd_back.c ft_swap_tab_int.c ft_is_this_char.c ft_strnstraf.c \
	   ft_realloc.c btree_create_node.c btree_search_item.c endian.c ft_atoi_base_64.c \
	   ft_hexa_to_uint64_t.c

OBJ_PATH = .obj/

CPPFLAGS = -Iinclude

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ) ./include
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	rm -fv $(NAME)

re: fclean all
