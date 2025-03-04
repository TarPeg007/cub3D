/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:00:55 by mzouine           #+#    #+#             */
/*   Updated: 2025/02/13 22:23:31 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

/*

FOV_ANGLE = POV * (PI / 180)
NUM_RAYS = width of the screen

rayAngle += FOV_ANGLE / NUM_RAYS
*/

float	mz_deg2rad(float degrees)
{
	return (degrees * (M_PI / 180));
}

float	mz_rad2deg(float radians)
{
	return (radians * (180 / M_PI));
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	mz_ray_caster(t_map_info *data)
{
	t_ray	ray;
	float	angle_incr;
	int		i;
	float	angle_start;
	float	inv_width;

	angle_start = data->rotation_angle - (M_PI / 6);
	inv_width = 1.0f / WIDTH;
	i = 0;
	ray.direction = 0;
	angle_incr = (M_PI / 3) * inv_width;
	ray.angle = normalize_angle(angle_start);
	while (i < WIDTH)
	{
		ft_dda(data, &ray);
		render_tex_col(data, &ray, i);
		ray.angle = normalize_angle(ray.angle + angle_incr);
		i++;
	}
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
