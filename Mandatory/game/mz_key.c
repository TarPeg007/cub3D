/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:10:56 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/22 11:03:22 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	mz_key(t_map_info *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		map->walk_dir = 1;
	else if (!mlx_is_key_down(map->mlx, MLX_KEY_W))
		map->walk_dir = 0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		map->walk_dir = -1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		map->strafe_dir = 1;
	else if (!mlx_is_key_down(map->mlx, MLX_KEY_D))
		map->strafe_dir = 0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		map->strafe_dir = -1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->turn_dir = 1;
	else if (!mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->turn_dir = 0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->turn_dir = -1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT_SHIFT))
		map->move_speed = TILE_SIZE / 2;
	if (!mlx_is_key_down(map->mlx, MLX_KEY_LEFT_SHIFT))
		map->move_speed = TILE_SIZE / 15;
}

void	mz_render(t_render_data *r_data)
{
	int			y;
	mlx_image_t	*current_texture;

	y = 0;
	r_data->data->ceiling_color_int
		= parse_rgb_string(r_data->data->ceiling_color);
	r_data->data->floor_color_int
		= parse_rgb_string(r_data->data->floor_color);
	select_texture(r_data->data, r_data->ray, &current_texture);
	r_data->current_texture = current_texture;
	r_data->tex_x = calculate_tex_x(r_data->ray, current_texture);
	while (y < r_data->wall_top && y < HEIGHT)
		mlx_put_pixel(r_data->data->imgg, r_data->x, y++,
			r_data->data->ceiling_color_int);
	while (y < r_data->wall_bottom && y < HEIGHT)
		render_wall_section(r_data, y++);
	while (y < HEIGHT)
		mlx_put_pixel(r_data->data->imgg, r_data->x, y++,
			r_data->data->floor_color_int);
}

void	render_tex_col(t_map_info *data, t_ray *ray, int x)
{
	t_render_data	r_data;
	float			wall_height;
	float			wall_top;
	float			wall_bottom;
	float			scale;

	scale = 64;
	wall_height = ((HEIGHT / ray->distance) * scale);
	ray->wall_height = wall_height;
	wall_top = (HEIGHT / 2) - (wall_height / 2);
	wall_bottom = wall_top + wall_height;
	r_data.data = data;
	r_data.wall_top = wall_top;
	r_data.wall_bottom = wall_bottom;
	r_data.x = x;
	r_data.ray = ray;
	mz_render(&r_data);
}

void	mz_ray_caster(t_map_info *data)
{
	t_ray	ray;
	float	angle_incr;
	int		i;

	i = 0;
	ray.direction = 0;
	angle_incr = (M_PI / 3) / WIDTH;
	ray.angle = normalize_angle(data->rotation_angle - (M_PI / 6));
	while (i < WIDTH)
	{
		ft_dda(data, &ray);
		render_tex_col(data, &ray, i);
		ray.angle = normalize_angle(ray.angle + angle_incr);
		i++;
	}
}

void	render_wall_section(t_render_data *r_data, int y)
{
	float		tex_y_ratio;
	uint32_t	color;

	tex_y_ratio = (y - r_data->wall_top)
		/ (r_data->wall_bottom - r_data->wall_top);
	r_data->tex_y = (int)(tex_y_ratio
			* r_data->current_texture->height);
	r_data->tex_y = fmin(r_data->tex_y,
			r_data->current_texture->height - 1);
	color = get_shaded_texture_color(r_data->current_texture,
			r_data->tex_x, r_data->tex_y);
	mlx_put_pixel(r_data->data->imgg, r_data->x, y, color);
}
