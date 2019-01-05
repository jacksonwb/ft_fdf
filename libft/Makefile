# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jackson <jbeall@student.42.us.org>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/22 16:25:23 by jbeall            #+#    #+#              #
#    Updated: 2018/12/14 21:46:20 by jackson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ./src/mem/ft_memcpy.c ./src/mem/ft_memmove.c ./src/mem/ft_memccpy.c \
./src/mem/ft_memchr.c ./src/mem/ft_bzero.c ./src/mem/ft_memdel.c \
./src/mem/ft_memalloc.c ./src/mem/ft_memcmp.c ./src/mem/ft_memset.c
SRC += ./src/print/ft_putstr.c ./src/print/ft_putnbr.c \
./src/print/ft_putstr_fd.c ./src/print/ft_putnbr_fd.c \
./src/print/ft_putendl_fd.c ./src/print/ft_putchar.c \
./src/print/ft_putendl.c ./src/print/ft_putchar_fd.c
SRC += ./src/conv/ft_itoa.c ./src/conv/ft_atoi.c ./src/conv/ft_ptoa.c
SRC += ./src/lst/ft_lstmap.c ./src/lst/ft_lstadd.c ./src/lst/ft_lstappend.c \
./src/lst/ft_lstiter.c ./src/lst/ft_lstrev.c ./src/lst/ft_lstdelone.c \
./src/lst/ft_lstnew.c ./src/lst/ft_lstcount.c ./src/lst/ft_lstdel.c
SRC += ./src/gnl/get_next_line.c
SRC += ./src/str/ft_strrchr.c ./src/str/ft_strcmp.c ./src/str/ft_strlcat.c \
./src/str/ft_strsplit.c ./src/str/ft_strncpy.c ./src/str/ft_wordcount.c \
./src/str/ft_striter.c ./src/str/ft_strstr.c ./src/str/ft_strdel.c \
./src/str/ft_countseg.c ./src/str/ft_strnjoin.c ./src/str/ft_strcpy.c \
./src/str/ft_strdup.c ./src/str/ft_striteri.c ./src/str/ft_strmap.c \
./src/str/ft_strrev.c ./src/str/ft_strnstr.c ./src/str/ft_strlen.c \
./src/str/ft_strsub.c ./src/str/ft_strnew.c ./src/str/ft_strsplit_lst.c \
./src/str/ft_strncat.c ./src/str/ft_strncmp.c ./src/str/ft_strtrim.c \
./src/str/ft_strequ.c ./src/str/ft_strcat.c ./src/str/ft_strnequ.c \
./src/str/ft_strjoin.c ./src/str/ft_strclr.c ./src/str/ft_strmapi.c \
./src/str/ft_strchr.c
SRC += ./src/char/ft_isspace.c ./src/char/ft_isdigit.c ./src/char/ft_isalnum.c \
./src/char/ft_toupper.c ./src/char/ft_isascii.c ./src/char/ft_isalpha.c \
./src/char/ft_tolower.c ./src/char/ft_isprint.c
SRC += ./src/math/pow_of_2.c ./src/math/pow_int.c ./src/math/ft_abs.c \
./src/math/itoa_len.c
SRC += ./src/sys/ft_die.c
SRC_FT_PRINTF := ft_printf.c parse.c utils_handlef_2.c handlef.c utils.c \
utils_handlef_3.c handler.c utils_handle.c utils_parse.c handler2.c \
utils_handlef.c
SRC_FT_PRINTF := $(addprefix ./src/ft_printf/, $(SRC_FT_PRINTF))
FLAGS = -Wall -Werror -Wextra -O3
OBJ = $(notdir $(SRC:.c=.o))
OBJ += $(notdir $(SRC_FT_PRINTF:.c=.o))
INC = ./includes

$(NAME): $(SRC)
	@echo "Building libft.a library..."
	@clang $(FLAGS) -c $(SRC) $(SRC_FT_PRINTF) -I$(INC)
	@ar -rc $(NAME) $(OBJ)
	@echo "\033[92mdone!\033[0m"
all: $(NAME)
clean:
	@echo "object files removed!"
	@rm -f *.o
fclean: clean
	@rm -f $(NAME)
	@echo "libft.a removed!"
re: fclean all
