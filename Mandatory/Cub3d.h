/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:04:13 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/22 08:32:23 by sfellahi         ###   ########.fr       */
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
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>

# define MAX_LINE_LENGTH 1024
# define MAX_MAP_SIZE 100

// MZOUINE PART!!!!!
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define TILE_SIZE			40 // should be able to be split by 2
# define MINMP_SIZE			2
# define WIDTH				1920 // 2600
# define HEIGHT				1080 // 1400
# define SCR_WIDTH			5120
# define SCR_HEIGHT			2880
# define HTBOX				0
# define FOV				60
# define WALL_STRIP_WIDTH 	1
# define NUM_RAYS  5120

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
	mlx_image_t		*imgg;
	mlx_t			*mlx;
	uint32_t		ceiling_color_int;
	uint32_t		floor_color_int;
	int				has_error;
	char			*error_message;
}	t_map_info;

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

typedef struct s_render_params
{
	float		wall_height;
	float		wall_top;
	float		wall_bottom;
	int			tex_x;
	int			tex_y;
	int			x;
	int			y;
	mlx_image_t	*texture;
	t_ray		*ray;
}	t_render_params;

typedef struct point
{
	float	x;
	float	y;
}	t_point;

typedef struct dda_step
{
	float	d_x;
	float	d_y;
	t_point	next;
	t_point	check_pt;
	float	distance;
}	t_dda;

char		*ft_strstr(const char *haystack, const char *needle);
void		*ft_memset(void *b, int c, size_t len);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(const char *s);
int			ft_strchr(char *s, char c);
char		*get_next_line(int fd);
char		*ft_ryhme(char *s);
void		ft_putstr_fd(char *str, int fd);
char		*next_ryhme(char *str);
void		check_args(int argc, char *argv[]);
t_map_info	*allocate_map(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		check_surroundings(t_map_info *info, int i, int j, int len);
void		handle_allocation_error(t_map_info *info, char *cleaned_line,
				char **new_map, int height);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *str);
void		process_map_line(char *line, t_map_info *info);
int			handle_f_c(char *trimmed, t_map_info *info);
void		check_map_borders(t_map_info *info);
void		update_map_info(t_map_info *info, char **new_map,
				char *cleaned_line);
int			is_valid_rgb(char *str);
int			validate_final(t_map_info *info);
void		load_textures(t_map_info *data);
void		process_map_line(char *line, t_map_info *info);
int			ft_isdigit(int c);
int			handle_line(char *line, t_map_info *info, int *map_started);
void		print_error(char *message, t_map_info *info);
void		init_map_info(t_map_info *info);
void		cleanup_map_info(t_map_info *info);
void		ft_free_array(char **arr);
char		*ft_strtrim(char const *s1, char const *set);
int			valid_map(char *filename, t_map_info *info);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
int			ft_max(int a, int b);
t_map_info	*parser(int argc, char *argv[]);
void		cleanup_map_info(t_map_info *info);
char		*ft_itoa(int n);

// static void validate_map_content(t_map_info *info);
// MZOUINE PART!!!!!

void		check_map_borders(t_map_info *info);
float		mz_deg2rad(float degrees);
void		mz_key(t_map_info *map);
uint32_t	get_shaded_texture_color(mlx_image_t *texture,
				int tex_x, int tex_y);
// static int	handle_we_ea(char *trimmed, t_map_info *info);
void		render_wall_section(t_render_data *r_data, int y);
int			calculate_tex_x(t_ray *ray, mlx_image_t *current_texture);
void		select_texture(t_map_info *data, t_ray *ray,
				mlx_image_t **current_texture);
size_t		get_max_len(t_map_info *info);
float		mz_rad2deg(float radians);
uint32_t	parse_rgb_string(char *rgb_str);
void		mz_draw(t_map_info *map);
void		mz_init_player(t_map_info *map);
void		mz_ray_caster(t_map_info *data);
void		mz_draw_line(t_map_info *map, int x2, int y2, int color);
int			get_rgba(int r, int g, int b, int a);
float		normalize_angle(float angle);
void		ft_dda(t_map_info *data, t_ray *ray);
float		get_distance(t_map_info *data, float x, float y);
int			is_wall(t_map_info *data, float x, float y);
int			is_right(float angle);
void		process_line_characters(char *clean_line,
				t_map_info *info, int height);
void		validate_map_chars(t_map_info *info, int i, size_t len);
int			is_up(float angle);
void		set_error(t_map_info *info, char *message);
// static int	handle_no_so(char *trimmed, t_map_info *info);
void		print_error(char *message, t_map_info *info);
void		validate_config(t_map_info *info);
size_t		get_max_len(t_map_info *info);
void		check_horizontal_borders(t_map_info *info, int max_len);
char		*clean_line(char *line, t_map_info *info);
char		**allocate_new_map(t_map_info *info, char *cleaned_line);
void		copy_existing_map(char **new_map, t_map_info *info);
int			check_commas(char *str);
int			validate_color_range(char **colors);
int			is_valid_identifier(char *line, t_map_info *info);
// static void process_map_line(char *line, t_map_info *info);
// MZOUINE PART!!!!!

#endif
