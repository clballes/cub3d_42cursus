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
GET_DIR = src/get_next_line/
MLX_DIR = mlx/
MLX = ${MLX_DIR}libmlx.a
MINILIBXCC	=  -L $(MLX_DIR) -lmlx
OPENGL = -framework OpenGL -framework AppKit

SRC_FILES = $(SRCS_DIR)main \
			$(SRCS_DIR)parsing \
			$(SRCS_DIR)parsing_utils \
			$(SRCS_DIR)elements \
			$(SRCS_DIR)free \
			$(GET_DIR)get_next_line \
			$(GET_DIR)get_next_line_utils

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
SRC 		+= 	$(addprefix $(GET_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR) $(SRCS_DIR)  #esta linea essta mal creo 
		echo "Compiling...[$<]"
		$(CC) -I$(INC_DIR) -I mlx -I$(LIBFT_DIR) -c $(CFLAGS)  $< -o $@


all: $(NAME)

$(LIBFT): 
		@make -C $(LIBFT_DIR)
$(MLX): 
		@make -C $(MLX_DIR)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) $(OBJ) $(MINILIBXCC) $(LINK) $(OPENGL) -o $(NAME)

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

-include ${DEPS}

.PHONY: all clean fclean re bonus