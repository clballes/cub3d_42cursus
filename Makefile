# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:55:16 by clballes          #+#    #+#              #
#    Updated: 2023/09/12 16:04:06 by albagarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD -g
RM = /bin/rm -rf

# Path
LIBFT_DIR = libft/
LIBFT = ${LIBFT_DIR}libft.a
LINK = -L$(LIBFT_DIR) -lft
SRC_DIR = src/
INC_DIR = inc/
MLX_DIR = mlx/
PARSE = parsing/
RENDER = rendering/
COLISION = colision/
MINIMAP = minimap/
MLX = ${MLX_DIR}libmlx.a
MINILIBXCC	=  -L $(MLX_DIR) -lmlx
OPENGL = -framework OpenGL -framework AppKit
OBJ_DIR = obj/
# FSANITIZE	:= -fsanitize=address

SRC_FILES = main \
			$(PARSE)init_parsing \
			$(PARSE)elements \
			$(PARSE)parsing_utils \
			$(PARSE)init_elements \
			$(PARSE)init_map \
			$(PARSE)map_valid \
			$(PARSE)free_parsing \
			$(PARSE)utils_rgb \
			$(PARSE)parse_textures \
			$(RENDER)render \
			$(RENDER)calculations \
			end_game \
			key_press \
			init \
			$(COLISION)draw_ray \
			$(COLISION)horizontal_colision \
			$(COLISION)vertical_colision \
			$(COLISION)utils_colision \
			$(MINIMAP)draw_minimap\
			$(MINIMAP)draw_empty_map\
			$(MINIMAP)checks_player\
			
			

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)
		mkdir -p $(OBJ_DIR)/parsing
		mkdir -p $(OBJ_DIR)/rendering
		mkdir -p $(OBJ_DIR)/colision
		mkdir -p $(OBJ_DIR)/minimap
		echo "Compiling...[$<]"
		$(CC) -I$(INC_DIR) -I mlx -I$(LIBFT_DIR) -c $(CFLAGS)  $< -o $@ 


all: makelib
	@$(MAKE) $(NAME)

makelib:
		@$(MAKE) -C $(LIBFT_DIR)
$(MLX): 
		@make -C $(MLX_DIR)

-include ${DEPS}
$(NAME): $(MLX) $(LIBFT) $(OBJ) Makefile
	make -sC $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) -o $(NAME) $(LIBFT) $(MINILIBXCC) $(LINK) $(OPENGL) 

clean:
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR) 
	rm -rf ${DEPS}
	make clean -sC $(LIBFT_DIR)
	make clean -sC $(MLX_DIR)
	@echo "\n🌼 It is all safe and clean 🌼\n"

fclean: clean
	make fclean -sC $(LIBFT_DIR)
	make fclean -sC $(MLX_DIR)

re: fclean all


.PHONY: all clean fclean re bonus