# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/01 14:21:53 by jbeall            #+#    #+#              #
#    Updated: 2019/01/04 22:48:32 by jbeall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FLAGS = -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit
SRC_DIR = ./src/
SRC = fdf.c fdf_parse.c fdf_parse2.c fdf_render.c fdf_draw.c fdf_draw2.c fdf_utils.c fdf_events.c
INC_DIR = ./includes/
LIB_INC_DIR = ./libft/includes/
LIB = ./libft/libft.a
MLX = ./minilibx_macos

$(NAME):
	@make -C ./libft --no-print-directory
	@echo "Building minilibx.a library..."
	@make -C ./minilibx_macos --no-print-directory
	@echo "\033[92mdone!\033[0m"
	@echo "Creating $(NAME) executable..."
	@gcc -o $(NAME) $(FLAGS) $(addprefix $(SRC_DIR), $(SRC)) $(LIB) -I$(LIB_INC_DIR) -I$(INC_DIR) -I$(MLX) -L$(MLX) -O3
	@echo "\033[92mdone!\033[0m"
all: $(NAME)
dev:
	@rm -f $(NAME)
	@make -C ./libft --no-print-directory
	@make -C ./minilibx_macos --no-print-directory
	@echo "compiling dev build..."
	@gcc -o $(NAME) $(FLAGS) -g $(addprefix $(SRC_DIR), $(SRC)) $(LIB) -I$(LIB_INC_DIR) -I$(INC_DIR) -I$(MLX) -L$(MLX)
	@echo "\033[92mdone!\033[0m"
clean:
	@echo "cleaning..."
	@make clean -C ./libft --no-print-directory
	@make clean -C ./minilibx_macos --no-print-directory
	@echo "minilibx objects removed!"
fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) executable removed!"
	@make fclean -C ./libft --no-print-directory
re: fclean all
