/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 13:48:18 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/16 16:43:29 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include "../get_next_line/get_next_line_bonus.h"

# define WIDTH 1280
# define HEIGHT 720
# define MIN_WIDTH 640
# define MIN_HEIGHT 360
# define TITLE "cub3D"

# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0
# define WALL_MARGIN 0.2
# define CAMERA_PLANE 0.66
# define ALPHA 255

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_COUNT 4

# define WALL '1'
# define WALKABLE '0'
# define SPACE ' '

# define N 'N'
# define S 'S'
# define E 'E'
# define W 'W'

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_scene
{
	t_map	map;
	t_rgb	floor;
	t_rgb	ceiling;
	char	*texture_path[TEX_COUNT];
}	t_scene;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			wall_dist;
	double			texture_step;
	double			texture_pos;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				texture_x;
	mlx_texture_t	*texture;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*texture[TEX_COUNT];
	t_scene			scene;
	t_player		player;
}	t_game;

// Graphics
bool		graphics_init(t_game *game);
bool		texture_load_all(t_game *game);
void		graphics_destroy(t_game *game);

// Rendering
void		render_frame(t_game *game);
void		render_loop(void *parameter);
void		ray_init(t_game *game, t_ray *ray, int x);
void		ray_dda(t_game *game, t_ray *ray);
void		ray_project(t_ray *ray);
void		ray_set_texture(t_game *game, t_ray *ray);
void		draw_column(t_game *game, t_ray *ray, int x);

// Player
bool		player_init(t_game *game);
void		player_input(t_game *game);
void		player_rotate(t_game *game, double angle);
void		player_try_move(t_game *game, double dx, double dy);

// Map
bool		map_is_wall(t_game *game, int x, int y);
bool		position_is_open(t_game *game, double x, double y);

// Utilities
uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

// Parser
bool		parse_scene(char *filename, t_scene *scene);
bool		parse_elements(int fd, t_scene *scene, char **first_map_line);
bool		elements_complete(t_scene *scene);
bool		parse_color(t_rgb *color, char *value);
bool		parse_map(int fd, t_scene *scene, char *first_line);
bool		validate_map(t_scene *scene);

// Parser helpers
bool		parse_error(char *message);
bool		is_direction(char c);
bool		is_blank_line(char *line);
bool		is_map_line(char *line);

#endif
