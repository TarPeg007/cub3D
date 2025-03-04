/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_dda2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:50:08 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/14 17:57:36 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_ray_direction(t_ray *ray, float angle)
{
	ray->ray_facing_up = is_up(angle);
	ray->ray_facing_left = !is_right(angle);
}

void	handle_vertical_hit(t_map_info *data, t_ray *ray, t_dda step_y,
		int is_door_vert)
{
	ray->distance = cos(data->rotation_angle - ray->angle) * step_y.distance;
	ray->end_x = step_y.next.x;
	ray->end_y = step_y.next.y;
	ray->is_a_door = is_door_vert;
	if (ray->is_a_door)
	{
		ray->direction = DOOR;
		if (ray->ray_facing_left)
			ray->door_qa = 1;
		else
			ray->door_qa = 0;
	}
	else
	{
		if (ray->ray_facing_left)
			ray->direction = WEST;
		else
			ray->direction = EAST;
	}
}

void	handle_horizontal_hit(t_map_info *data, t_ray *ray, t_dda step_x,
		int is_door_hor)
{
	ray->distance = cos(data->rotation_angle - ray->angle) * step_x.distance;
	ray->end_x = step_x.next.x;
	ray->end_y = step_x.next.y;
	ray->is_a_door = is_door_hor;
	if (ray->is_a_door)
	{
		ray->direction = DOOR;
		if (ray->ray_facing_up)
			ray->door_qa = 1;
		else
			ray->door_qa = 0;
	}
	else
	{
		if (ray->ray_facing_up)
			ray->direction = NORTH;
		else
			ray->direction = SOUTH;
	}
}

void	select_texture(t_map_info *data, t_ray *ray,
		mlx_image_t **current_texture)
{
	*current_texture = NULL;
	if (ray->direction == DOOR && data->door_img)
		*current_texture = data->door_img;
	else if (ray->direction == NORTH && data->north_img)
		*current_texture = data->north_img;
	else if (ray->direction == SOUTH && data->south_img)
		*current_texture = data->south_img;
	else if (ray->direction == EAST && data->east_img)
		*current_texture = data->east_img;
	else if (ray->direction == WEST && data->west_img)
		*current_texture = data->west_img;
}

void	ft_dda(t_map_info *data, t_ray *ray)
{
	t_dda	step_x;
	t_dda	step_y;
	int		is_door_hor;
	int		is_door_vert;

	data->ray.is_a_door = 0;
	step_y = get_vert_inters(data, ray->angle);
	is_door_vert = data->ray.is_a_door;
	step_x = get_hor_inters(data, ray->angle);
	is_door_hor = data->ray.is_a_door;
	init_ray_direction(ray, ray->angle);
	ray->is_ver = (step_x.distance > step_y.distance);
	if (step_x.distance > step_y.distance)
		handle_vertical_hit(data, ray, step_y, is_door_vert);
	else
		handle_horizontal_hit(data, ray, step_x, is_door_hor);
	if (ray->is_a_door)
	{
		ray->wall_hit_x = ray->end_x;
		ray->wall_hit_y = ray->end_y;
	}
}
