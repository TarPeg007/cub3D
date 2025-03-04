/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:04:13 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/22 08:32:44 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define DOOR 4
# define MAX_LINE_LENGTH 1024
# define MAX_MAP_SIZE 100

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define TILE_SIZE 40
# define MINMP_SIZE 2
# define WIDTH 1920
# define HEIGHT 1080
# define SCR_WIDTH 5120
# define SCR_HEIGHT 2880
# define HTBOX 0
# define FOV 60
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS 5120

# define PATH_WEAPON_INIT_STATE "Bonus/weapon/init_state/0.png"
# define PATH_WEAPON_NORMAL_SHOOT "Bonus/weapon/normal_shoot/img"
# define PATH_WEAPON_ZOOM_SHOOT "Bonus/weapon/zome_shoot/img"
# define PATH_WEAPON_RELOAD "Bonus/weapon/reload/img"
# define PNG ".png"
# define FRAMES_SHOOT 18
# define FRAMES_RELOAD 84
# define FRAMES_ZOOM 19
# define WEAPON_Y 396
# define WEAPON_X 350

# define RELOAD_SOUND_PATH "Bonus/sounds/music/reload_sound.mp3"
# define SHOOT_SOUND_PATH "Bonus/sounds/music/shoot_sound.mp3"

typedef struct s_sound_thread
{
	pthread_t		id_background_music;
	pthread_t		id_sound;
	bool			is_playing_bg;
	bool			is_playing_sound;
	bool			should_exit;
	pthread_mutex_t	mutex;
}	t_sound_thread;

typedef struct s_sound
{
	t_sound_thread	thread;
	int				play_shoot;
	int				play_reload;
}	t_sound;

typedef struct s_crosshair
{
	mlx_image_t		*image;
	int				size;
	int				thickness;
	int				color;
}	t_crosshair;

typedef struct s_gun
{
	mlx_texture_t	*textures[40];
	mlx_image_t		*images[40];
	int				current_frame;
	bool			is_animating;
	double			anim_start_time;
	bool			is_shooting;
	int				width;
	int				height;
	int				total_shoot_frames;
	bool			is_reloading;
	bool			is_zooming;
	bool			init_state;
	int				frame_counter;
}	t_gun;

typedef struct s_door
{
	int	x;
	int	y;
	int	is_open;
}	t_door;

typedef struct s_ray
{
	float	end_x;
	float	end_y;
	float	angle;
	float	distance;
	int		direction;
	int		is_a_door;
	float	dist_proj_plan;
	float	wall_height;
	int		ray_facing_down;
	int		ray_facing_left;
	int		r;
	int		g;
	int		b;
	int		a;
	int		door_qa;
	int		is_ver;
	int		ray_facing_up;
	int		ray_facing_right;
	float	wall_hit_x;
	float	wall_hit_y;
	int		is_door;
}	t_ray;

typedef struct s_render_params
{
	float	wall_top;
	float	wall_bottom;
	int		x;
	t_ray	*ray;
}	t_render_params;

typedef struct s_text_effect
{
	bool			is_active;
	double			start_time;
	mlx_image_t		*text_image;
	mlx_texture_t	*text_texture;
}	t_text_effect;

typedef struct s_norm
{
	int	i;
	int	j;
	int	x;
	int	y;
}	t_norm;

typedef struct s_map_info
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*floor_color;
	char			*ceiling_color;
	char			**map;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_image_t		*east_img;
	mlx_image_t		*west_img;
	mlx_image_t		*north_img;
	mlx_image_t		*south_img;
	int				map_height;
	int				map_width;
	int				player_count;
	int				config_count;
	int				parsing_map;
	float			p_x;
	float			p_y;
	char			p_orient;
	float			ray_x;
	float			ray_y;
	int				turn_dir;
	int				walk_dir;
	float			rotation_angle;
	int				move_speed;
	float			rotation_speed;
	float			move_step;
	float			time;
	int				offset_x;
	int				offset_y;
	int				strafe_dir;
	t_door			*doors;
	t_ray			ray;
	int				door_count;
	t_gun			*gun;
	t_text_effect	text_effect;
	int				color_effect_enabled;
	mlx_image_t		*imgg;
	mlx_t			*mlx;
	mlx_texture_t	*door_texture;
	mlx_image_t		*door_img;
	t_sound			*sound;
	t_crosshair		*crosshair;
	t_norm			*norm;
	uint32_t		ceiling_color_int;
	uint32_t		floor_color_int;
	int				has_error;
	char			*error_message;
}	t_map_info;

typedef struct s_render_data
{
	t_map_info	*data;
	float		wall_top;
	float		wall_bottom;
	int			x;
	t_ray		*ray;
	mlx_image_t	*current_texture;
	int			tex_x;
	int			tex_y;
}	t_render_data;

typedef struct s_line
{
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

typedef struct s_draw_params
{
	t_map_info	*map;
	t_line		*line;
	int			x2;
	int			y2;
}	t_draw_params;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_dda_step
{
	float	d_x;
	float	d_y;
	t_point	next;
	t_point	check_pt;
	float	distance;
}	t_dda;

typedef struct s_line_params
{
	int	x2;
	int	y2;
	int	color;
}	t_line_params;

char		*ft_strstr(const char *haystack, const char *needle);
void		*ft_memset(void *b, int c, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		init_ray_direction(t_ray *ray, float angle);
size_t		ft_strlen(const char *s);
int			ft_strchr(char *s, char c);
void		handle_doors(t_map_info *map);
void		mz_render(t_render_data *r_data);
void		draw_pixels(t_map_info *map, t_line *line, t_point end, int color);
void		mz_draw(t_map_info *map);
void		calc_ray_pos(t_map_info *map, int *pos, int dx, int dy);
char		*get_next_line(int fd);
char		*ft_ryhme(char *s);
void		init_line(t_line *line, t_point start, t_point end);
void		update_rotation(t_map_info *map);
void		ft_putstr_fd(char *str, int fd);
void		set_error(t_map_info *info, char *message);
char		*next_ryhme(char *str);
void		mz_draw_minimap_grid(t_map_info *map);
char		**ft_split(char const *s, char c);
void		validate_map_chars(t_map_info *info, int i, size_t len);
int			ft_atoi(const char *str);
int			update_ray_position(t_map_info *map, int *pos, int x1, int y1);
void		mouse_rotate(t_map_info *map);
void		process_map_line(char *line, t_map_info *info);
void		check_map_borders(t_map_info *info);
int			is_valid_rgb(char *str);
void		load_textures(t_map_info *data);
int			ft_isdigit(int c);
void		handle_doors(t_map_info *map);
char		*safe_strjoin(char *s1, char *s2, t_map_info *map);
void		handle_horizontal_hit(t_map_info *data, t_ray *ray,
				t_dda step_x, int is_door_hor);
void		init_gun(t_map_info *map);
void		select_texture(t_map_info *data, t_ray *ray,
				mlx_image_t **current_texture);
float		get_distance(t_map_info *data, float x, float y);
void		*sound_effects_routine(void *arg);
void		init_sound_system(t_map_info *map);
void		check_sound_files(t_map_info *map);
void		cleanup_gun(t_map_info *map);
mlx_image_t	*play_weapon(t_map_info *map);
mlx_image_t	*play_weapon_status(t_map_info *map, int max_frames, char *path);
void		print_error(char *message, t_map_info *info);
void		handle_vertical_hit(t_map_info *data, t_ray *ray,
				t_dda step_y, int is_door_vert);
void		init_map_info(t_map_info *info);
void		cleanup_map_info(t_map_info *info);
void		ft_free_array(char **arr);
void		init_doors(t_map_info *data);
char		*ft_strtrim(char const *s1, char const *set);
int			valid_map(const char *filename, t_map_info *info);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
int			ft_max(int a, int b);
t_map_info	*parser(int argc, char *argv[]);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
float		mz_deg2rad(float degrees);
float		mz_rad2deg(float radians);
void		mz_draw(t_map_info *map);
void		ft_dda(t_map_info *data, t_ray *ray);
float		normalize_angle(float angle);
void		mz_init_player(t_map_info *map);
void		mz_ray_caster(t_map_info *data);
void		mz_draw_line(t_map_info *map, t_point end, int color);
int			get_rgba(int r, int g, int b, int a);
void		handle_player_position(char c, int x, t_map_info *info, int height);
void		handle_door_position(int x, t_map_info *info, int height);
char		*clean_line(char *line, t_map_info *info);
char		**allocate_new_map(t_map_info *info, char *cleaned_line);
void		mz_draw_minimap(t_map_info *map);
void		mz_move_player(t_map_info *map);
void		mz_draw_minimap(t_map_info *map);
t_dda		get_vert_inters(t_map_info *data, float angle);
int			is_wall(t_map_info **data, float x, float y);
void		mz_key(t_map_info *map);
t_dda		get_hor_inters(t_map_info *data, float angle);
int			is_up(float angle);
int			is_right(float angle);
void		check_surroundings(t_map_info *info, int i, size_t j, size_t len);
size_t		get_max_len(t_map_info *info);
void		copy_existing_map(char **new_map, t_map_info *info);
void		check_horizontal_borders(t_map_info *info, size_t max_len);
void		check_vertical_borders(t_map_info *info, int i, size_t len);
void		init_gun(t_map_info *map);
int			is_valid_door_pos(t_map_info *map, int x, int y);
void		update_gun_animation(t_map_info *map);
void		update_door_state(t_map_info *map, t_door *door, float distance);
void		handle_gun_shooting(t_map_info *map);
void		cleanup_gun(t_map_info *map);
void		render_tex_col(t_map_info *data, t_ray *ray, int x);
void		mz_draw_player(t_map_info *map, int radius, int color);
void		mz_draw_ray(t_map_info *map, int x2, int y2, int color);
void		calc_ray_pos(t_map_info *map, int *pos, int dx, int dy);
mlx_image_t	*play_weapon(t_map_info *map);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_itoa(int n);
mlx_image_t	*play_weapon_status(t_map_info *map, int max_frames, char *path);
int			is_valid_texture_path(char *path);
int			is_valid_identifier(char *line, t_map_info *info);
void		init_sound_system(t_map_info *map);
void		validate_config(t_map_info *info);
void		cleanup_sound_system(t_map_info *map);
void		init_crosshair(t_map_info *map);
void		update_gun_animation(t_map_info *map);
void		handle_gun_shooting(t_map_info *map);
int			handle_line(char *line, t_map_info *info, int *map_started);
void		cleanup_gun(t_map_info *map);
void		handle_gun_shooting(t_map_info *map);
void		handle_gun_action(t_map_info *map, int action);
char		*create_weapon_path(t_map_info *map, char *path);
mlx_image_t	*create_weapon_image(t_map_info *map, char *full_path);
void		update_weapon_state(t_map_info *map, int max_frames);
mlx_image_t	*play_weapon(t_map_info *map);
void		*ft_calloc(size_t count, size_t size);
void		cleanup_crosshair(t_map_info *map);
mlx_image_t	*play_init_state(t_map_info *map);
void		ft_bzero(void *s, size_t n);
void		render_crosshair(t_map_info *map);
uint32_t	get_shaded_texture_color(mlx_image_t *texture,
				int tex_x, int tex_y);

#endif