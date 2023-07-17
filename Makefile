# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clballes <clballes@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:55:16 by clballes          #+#    #+#              #
#    Updated: 2023/02/23 14:55:42 by clballes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD
RM = /bin/rm -rf

# Path
LIBFT_DIR = libft/
LIBFT = ${LIBFT_DIR}libft.a
LINK = -L$(LIBFT_DIR) -lft
SRCS_DIR = src/
INC_DIR = inc/
MLX_DIR = mlx/
MLX = ${MLX_DIR}libmlx.a
MINILIBXCC	=  -L $(MLX_DIR) -lmlx
OPENGL = -framework OpenGL -framework AppKit

SRCS = $(SRCS_DIR)main.c
OBJ = $(SRCS:%.c=%.o)
DEPS = $(SRCS:%.c=%.d)

# Gcc
$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) $(OBJ) $(MINILIBXCC) $(LINK) $(OPENGL) -o $(NAME)

$(LIBFT): 
		@make -C $(LIBFT_DIR)
$(MLX): 
		@make -C $(MLX_DIR)

%.o: %.c Makefile
	echo "Compiling...[$<]"
	$(CC) -I$(INC_DIR) -I mlx -I$(LIBFT_DIR) -c $(CFLAGS)  $< -o $@

clean:
	$(RM) $(NAME)
	$(RM) $(OBJ) 
	rm -rf ${DEPS}
	make clean -sC $(LIBFT_DIR)
	make clean -sC $(MLX_DIR)
	echo "\n🌼 It is all safe and clean 🌼\n"

fclean: clean
	make fclean -sC $(LIBFT_DIR)
	make fclean -sC $(MLX_DIR)

re: fclean all

all: $(NAME)

-include ${DEPS}

.PHONY: all clean fclean re bonus