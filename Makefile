NAME    = cub3D
CC      = cc
FLAGS   = -Wall -Wextra -Werror
RM      = rm -f

MLX_DIR = ../MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include
GLFW    = $(shell pkg-config --libs glfw3 2>/dev/null || echo "-L/opt/homebrew/lib -lglfw")
MLX_LNK = $(MLX_LIB) $(GLFW) -framework Cocoa -framework OpenGL -framework IOKit -lm

INC     = -Iincludes $(MLX_INC)

SRCS    = src/main.c \
          src/parsing/parse_file.c \
          src/parsing/parse_elements.c \
          src/parsing/parse_map.c \
          src/parsing/validate_map.c \
          src/mlx/mlx_init.c \
          src/mlx/mlx_utils.c \
          src/textures/texture_load.c \
          src/player/player.c \
          src/events/events.c \
          src/raycast/raycast.c \
          src/render/render_frame.c \
          src/render/render_wall.c \
          src/render/render_flat.c \
          src/cleanup/cleanup.c \
          src/utils/utils.c \
          src/utils/gnl.c

OBJS    = $(SRCS:.c=.o)
HEADERS = includes/cub3d.h

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(MLX_LNK) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
