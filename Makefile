# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/04 20:20:04 by waroonwork@       #+#    #+#              #
#    Updated: 2026/08/01 15:14:18 by waroonwork@      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	cub3D

CC				:=	cc
AR				:=	ar rcs
CFLAGS			:=	-Wall -Wextra -Werror -g3

# Linking differs per OS: macOS needs Apple frameworks instead of dl/pthread
UNAME			:=	$(shell uname)
ifeq ($(UNAME), Darwin)
GLFW_FLAGS		:=	$(shell pkg-config --libs glfw3 2>/dev/null \
						|| echo "-L/opt/homebrew/lib -lglfw")
LDFLAGS			:=	$(GLFW_FLAGS) -framework Cocoa -framework OpenGL \
					-framework IOKit -lm
else
LDFLAGS			:=	-ldl -lglfw -pthread -lm
endif

# Project
INC_DIR			:=	includes/
SRCS_DIR		:=	src/
SRCS_FILES		:=	main.c \
					graphics/graphics_destroy.c graphics/graphics_init.c graphics/texture_load.c \
					map/map_access.c \
					parser/parse_color.c parser/parse_elements.c parser/parse_file.c parser/parse_map.c parser/parse_utils.c parser/validate_map.c \
					player/player_init.c player/player_input.c player/player_move.c player/player_rotate.c \
					render/draw_column.c render/ray_dda.c render/ray_init.c render/ray_projection.c render/ray_texture.c render/render_frame.c \
					utils/color.c
SRCS			:=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS			:=	$(SRCS:.c=.o)

# Libft
LIBFT_DIR		:=	libft/
LIBFT_INC_DIR	:=	$(LIBFT_DIR)includes/
LIBFT			:=	libft.a

# Get Next Line
GNL_DIR			:=	get_next_line/
GNL_INC_DIR		:=	$(GNL_DIR)
GNL				:=	libgnl.a
GNL_SRCS		:=	$(GNL_DIR)get_next_line_bonus.c \
					$(GNL_DIR)get_next_line_utils_bonus.c
GNL_OBJS		:=	$(GNL_SRCS:.c=.o)

# MLX42
MLX42_DIR		:=	MLX42/
MLX42_INC_DIR	:=	$(MLX42_DIR)include/
MLX42			:=	libmlx42.a

# Include flags
CPPFLAGS		:=	-I$(INC_DIR) \
					-I$(LIBFT_INC_DIR) \
					-I$(GNL_INC_DIR) \
					-I$(MLX42_INC_DIR)

# Main rule
# Build order:
# 1. MLX42
# 2. Libft
# 3. GNL
# 4. Project source objects
# 5. Final executable
all				:
	$(MAKE) $(MLX42)
	$(MAKE) $(LIBFT)
	$(MAKE) $(GNL)
	$(MAKE) $(OBJS)
	$(MAKE) $(NAME)

# Final executable
$(NAME)			:	$(OBJS) $(LIBFT) $(GNL) $(MLX42) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) $(MLX42) \
		$(LDFLAGS) -o $@

# Project object files
$(SRCS_DIR)%.o	:	$(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Libft
libft			:	$(LIBFT)

$(LIBFT)		:
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)libft.a $(LIBFT)

# Get Next Line
gnl				:	$(GNL)

$(GNL)			:	$(GNL_OBJS)
	$(AR) $@ $^

$(GNL_DIR)%.o	:	$(GNL_DIR)%.c
	$(CC) $(CFLAGS) -I$(GNL_INC_DIR) -c $< -o $@

# MLX42
mlx				:	$(MLX42)

$(MLX42)		:	$(MLX42_DIR)
	cd $(MLX42_DIR) && cmake -B build
	cd $(MLX42_DIR) && cmake --build build -j4
	cp $(MLX42_DIR)/build/$(MLX42) .

$(MLX42_DIR)	:
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)

# Cleaning
clean			:
	rm -f $(OBJS)
	rm -f $(GNL_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean			:	clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(GNL)
	rm -f $(MLX42)
	rm -rf $(MLX42_DIR)

re				:	fclean
	$(MAKE) all

bonus			:	all

.PHONY			:	all clean fclean re bonus libft gnl mlx
