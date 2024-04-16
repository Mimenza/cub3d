# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 10:48:36 by emimenza          #+#    #+#              #
#    Updated: 2024/04/16 10:12:06 by emimenza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definir colores
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No color (reiniciar)

#Comandos
DEL			=	rm -f
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror
MLX			=	-framework OpenGL -framework AppKit
#MLX			=	-lXext -lX11 -lm -lbsd
# -g3 -fsanitize=address

#Nombre ejecutable
NAME		=	cub3d

#Ficheros
SRC_FILES	=	00_main 01_game 02_map 03_map_utils1 04_map_utils2 05_window 08_free 09_error 10_print_map
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

MINILIBX	=	libs/minilibx
GNL			=	libs/gnl
LIBFT		=	libs/Libft

#Librerias 
LIBS		= $(MINILIBX)/libmlx.a $(MLX) $(GNL)/get_next_line.a $(LIBFT)/libft.a 

#Directorios
SRC_DIR = srcs/
OBJ_DIR = objs/

# REGLAS # 
all:	minilibx gnl libft $(NAME)

#Compilar 
$(NAME):$(OBJ)
		@$(CC) $(OBJ) $(LIBS) -o $(NAME)
		@echo "$(GREEN)CUB3D HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(NC)"
	@$(CC) $(CFLAGS) -o $@ -c $< 
	@echo "$(YELLOW)Compiled!$(NC)"
	
# $@ : The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file.
# $< : The name of the first prerequisite.

#compilar librerias individuales
libft:
	@echo "$(YELLOW)COMPILING LIBFT...$(NC)"
	@$(MAKE) -C ./$(LIBFT)
	@echo "$(GREEN)LIBFT HAS BEEN COMPILED$(NC)"

minilibx:
	@echo "$(YELLOW)COMPILING MINILIBX...$(NC)"
	@$(MAKE) -C ./$(MINILIBX)
	@echo "$(GREEN)MINILIBX HAS BEEN COMPILED$(NC)"

gnl:
	@echo "$(YELLOW)COMPILING GNL...$(NC)"
	@$(MAKE) -C ./$(GNL)
	@echo "$(GREEN)GNL HAS BEEN COMPILED$(NC)"

# Eliminar tmp mlx
fclean_mlx:
	@make fclean -C ./$(MINILIBX)
	@echo "$(RED)MINILIBX FULL CLEANED!$(NC)"

# Eliminar tmp gnl
fclean_gnl:
	@make fclean -C ./$(GNL)
	@echo "$(RED)GNL FULL CLEANED!$(NC)"

# Eliminar tmp libft
fclean_libft:
	@make fclean -C ./$(LIBFT)
	@echo "$(RED)LIBFT FULL CLEANED!$(NC)"

# Eliminar temporales
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"


# Eliminar temporales y ejecutable fclean_mlx
fclean: clean  fclean_gnl fclean_libft
	@$(RM) $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"


re: fclean all