/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_dda3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:30:09 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/13 15:13:44 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

float	get_distance(t_map_info *data, float x, float y)
{
	float	delta_x;
	float	delta_y;

	delta_x = x - data->p_x;
	delta_y = y - data->p_y;
	return (sqrt((delta_x * delta_x) + (delta_y * delta_y)));
}

int	is_up(float angle)
{
	return (angle > M_PI);
}

int	is_wall(t_map_info **data, float x, float y)
{
	int		map_x;
	int		map_y;

	map_x = (int)x / TILE_SIZE;
	map_y = (int)y / TILE_SIZE;
	if (map_x >= 0 && map_x < (*data)->map_width
		&& map_y >= 0 && map_y < (*data)->map_height)
	{
		if ((*data)->map[map_y][map_x] == '1')
		{
			(*data)->ray.is_a_door = 0;
			return (1);
		}
		else if ((*data)->map[map_y][map_x] == 'D')
		{
			(*data)->ray.is_a_door = 1;
			(*data)->ray.direction = DOOR;
			(*data)->ray.wall_hit_x = x;
			(*data)->ray.wall_hit_y = y;
			return (1);
		}
		return (0);
	}
	return (1);
}
