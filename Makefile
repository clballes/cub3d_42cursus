# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:55:16 by clballes          #+#    #+#              #
#    Updated: 2023/07/18 16:18:01 by albagarc         ###   ########.fr        #
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
SRC_DIR = src/
INC_DIR = inc/
MLX_DIR = mlx/
MLX = ${MLX_DIR}libmlx.a
MINILIBXCC	=  -L $(MLX_DIR) -lmlx
OPENGL = -framework OpenGL -framework AppKit
OBJ_DIR = obj/

SRC_FILES = main \
			parsing \
			end_game \
			key_press \
			draw_minimap \
			
			

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)   
		echo "Compiling...[$<]"
		$(CC) -I$(INC_DIR) -I mlx -I$(LIBFT_DIR) -c $(CFLAGS)  $< -o $@


all: $(NAME)

$(LIBFT): 
		@make -C $(LIBFT_DIR)
$(MLX): 
		@make -C $(MLX_DIR)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
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