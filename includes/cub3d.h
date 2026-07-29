#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include "MLX42/MLX42.h"

/* ─── Screen ─────────────────────────────── */
# define WIDTH   1280
# define HEIGHT  720
# define TITLE   "cub3D"

/* ─── Movement tuning ────────────────────── */
# define MOVE_SPEED  0.05
# define ROT_SPEED   0.03
# define WALL_MARGIN 0.2

/* ─── Texture side index (order matters) ─── */
# define NO 0
# define SO 1
# define WE 2
# define EA 3

/* ─── Key bindings (MLX42 keysyms) ───────── */
# define KEY_W     MLX_KEY_W
# define KEY_A     MLX_KEY_A
# define KEY_S     MLX_KEY_S
# define KEY_D     MLX_KEY_D
# define KEY_LEFT  MLX_KEY_LEFT
# define KEY_RIGHT MLX_KEY_RIGHT
# define KEY_ESC   MLX_KEY_ESCAPE

/* ─── get_next_line ──────────────────────── */
# define BUFFER_SIZE 1024

/*
 * ================= DATA MODEL =================
 * ownership rule: t_game เป็นเจ้าของทุกอย่าง.
 * ทุก alloc ต้องถูก free ที่ cleanup ที่เดียว.
 * =============================================
 */

typedef struct s_img
{
	mlx_image_t		*img;
	mlx_texture_t	*tex;
	int				width;
	int				height;
}	t_img;

typedef struct s_mlx
{
	mlx_t	*mlx;
	t_img	screen;
}	t_mlx;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move_fb;
	int		move_lr;
	int		rotate;
}	t_player;

// ทิศที่มอง: dir_x, dir_y + กล้อง: plane_x, plane_y
// dir = unit vector ชี้ไปทางที่ player หันหน้า
// plane = vector ตั้งฉากกับ dir แทน "ความกว้างของจอที่ฉาย ray ออกไป"
// ความยาวของ plane เทียบกับ dir คือ FOV — ถ้า |dir|=1.0 แล้ว |plane|≈0.66 จะได้ FOV ประมาณ 66° (ค่ามาตรฐาน Wolfenstein-style)
// ตอนหมุนกล้อง (←/→) ทั้ง dir และ plane ต้องหมุนไปด้วยกันด้วย rotation matrix เดียวกัน ไม่งั้นมุมกล้องจะเพี้ยน

// Input flags: move_fb, move_lr, rotate
// ไม่ใช่ boolean เดียว แต่เป็น int (+1 / -1 / 0) เพราะต้องบอกทิศทางด้วย
// คำถามสำคัญ: ทำไมไม่ให้ key_hook แก้ pos_x/dir ตรงๆ เลย?
// เพราะ MLX เรียก key_hook แค่ตอน event เปลี่ยนสถานะ (กดครั้งแรก / ปล่อย) ไม่ได้เรียกซ้ำทุก frame ตอนกดค้าง ถ้าไปแก้ตำแหน่งใน key_hook ตรงๆ → เดินได้แค่ "กระตุกทีเดียว" ตอนกดปุ่ม ไม่ smooth
// Pattern ที่ถูกคือแยก 2 หน้าที่
// key_hook   → แค่ set/clear flag  (move_fb = 1 ตอนกด W, = 0 ตอนปล่อย)
// loop_hook  → ทุก frame อ่าน flag แล้วค่อยขยับ pos_x/pos_y จริง

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	t_img		tex[4];
	char		*tex_path[4];
	int			floor_color;
	int			ceil_color;
	int			has_floor;
	int			has_ceil;
}	t_game;

/* ================= PROTOTYPES ================= */

/* parsing */
int		parse_cub(t_game *game, char *path);
int		parse_elements(t_game *game, int fd, char **first_map_line);
int		parse_element_line(t_game *game, char *line);
int		parse_map(t_game *game, int fd, char *first_line);
int		validate_map(t_game *game);

/* mlx */
int		init_mlx(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);

/* textures */
int		load_textures(t_game *game);

/* player */
void	init_player(t_game *game, int x, int y, char dir);
void	update_player(t_game *game);
int		is_blocked(t_game *game, double x, double y);

/* events */
void	key_hook(mlx_key_data_t kd, void *param);
void	loop_hook(void *param);
void	close_hook(void *param);

/* raycast */
void	init_ray(t_ray *ray, t_player *p, int x);
void	init_step(t_ray *ray, t_player *p);
void	perform_dda(t_ray *ray, t_game *game);
void	calc_wall_data(t_ray *ray);

/* render */
void	render_frame(t_game *game);
void	draw_column(t_game *game, t_ray *ray, int x);
void	draw_background(t_game *game);

/* cleanup */
int		cleanup_exit(t_game *game, char *msg, int code);

/* utils */
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(const char *s, char c);
void	ft_free_split(char **arr);

/* gnl */
char	*get_next_line(int fd);

#endif
