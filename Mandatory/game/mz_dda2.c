/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_dda2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:18:28 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/13 20:40:50 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	find_wall(t_map_info *data, t_dda *step)
{
	while (1)
	{
		if (is_wall(data, step->check_pt.x, step->check_pt.y))
			break ;
		step->next.x += step->d_x;
		step->next.y += step->d_y;
		step->check_pt.x += step->d_x;
		step->check_pt.y += step->d_y;
	}
	step->distance = get_distance(data, step->next.x, step->next.y);
}

t_dda	get_hor_inters(t_map_info *data, float angle)
{
	t_dda	step;

	step.next.y = (floor(data->p_y / TILE_SIZE) * TILE_SIZE);
	step.check_pt.y = step.next.y;
	step.d_y = TILE_SIZE;
	if (!is_up(angle))
	{
		step.next.y += TILE_SIZE;
		step.check_pt.y += TILE_SIZE + 1;
	}
	else
	{
		step.d_y *= -1;
		step.check_pt.y -= 1;
	}
	step.next.x = data->p_x + (step.next.y - data->p_y) / tan(angle);
	step.check_pt.x = step.next.x;
	step.d_x = TILE_SIZE / tan(angle);
	if (!is_right(angle) && step.d_x > 0)
		step.d_x *= -1;
	if (is_right(angle) && step.d_x < 0)
		step.d_x *= -1;
	return (find_wall(data, &step), step);
}

t_dda	get_vert_inters(t_map_info *data, float angle)
{
	t_dda	step;

	step.next.x = (floor(data->p_x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	step.check_pt.x = step.next.x;
	step.d_x = TILE_SIZE;
	if (!is_right(angle))
	{
		step.next.x -= TILE_SIZE;
		step.check_pt.x -= (TILE_SIZE + 1);
		step.d_x *= -1;
	}
	else
		step.check_pt.x += 1;
	step.next.y = data->p_y + (step.next.x - data->p_x) * tan(angle);
	step.check_pt.y = step.next.y;
	step.d_y = TILE_SIZE * tan(angle);
	if (is_up(angle) && step.d_y > 0)
		step.d_y *= -1;
	if (!is_up(angle) && step.d_y < 0)
		step.d_y *= -1;
	return (find_wall(data, &step), step);
}

void	set_ray_properties(t_ray *ray, t_dda step,
	float distortion_factor, int direction)
{
	ray->direction = direction;
	ray->distance = distortion_factor * step.distance;
	ray->end_x = step.next.x;
	ray->end_y = step.next.y;
	if (direction == EAST || direction == WEST)
		ray->end_x -= (direction == EAST);
	else
		ray->end_y -= (direction != SOUTH);
}

void	ft_dda(t_map_info *data, t_ray *ray)
{
	t_dda	step_x;
	t_dda	step_y;
	float	distortion_factor;
	int		direction;

	step_x = get_hor_inters(data, ray->angle);
	step_y = get_vert_inters(data, ray->angle);
	distortion_factor = cos(data->rotation_angle - ray->angle);
	if (step_x.distance > step_y.distance)
	{
		if (is_right(ray->angle))
			direction = EAST;
		else
			direction = WEST;
		set_ray_properties(ray, step_y, distortion_factor, direction);
	}
	else
	{
		if (is_up(ray->angle))
			direction = SOUTH;
		else
			direction = NORTH;
		set_ray_properties(ray, step_x, distortion_factor, direction);
	}
}
