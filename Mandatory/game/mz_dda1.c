/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_dda1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:17:24 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/16 13:06:16 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	is_wall(t_map_info *data, float x, float y)
{
	int	map_x;
	int	map_y;

	if (!data || !data->map || data->map_width <= 0 || data->map_height <= 0)
		return (1);
	if (x < 0 || y < 0 || x >= (data->map_width * TILE_SIZE)
		|| y >= (data->map_height * TILE_SIZE))
		return (1);
	map_x = (int)x / TILE_SIZE;
	map_y = (int)y / TILE_SIZE;
	if (map_x < 0 || map_x >= data->map_width
		|| map_y < 0 || map_y >= data->map_height)
		return (1);
	if (!data->map[map_y] || ft_strlen(data->map[map_y]) <= map_x)
		return (1);
	return (data->map[map_y][map_x] != '0');
}

float	normalize_angle(float angle)
{
	float	normalized;

	normalized = fmod(angle, 2 * M_PI);
	if (normalized < 0.0)
		normalized += 2 * M_PI;
	return (normalized);
}

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

int	is_right(float angle)
{
	return (angle >= (3 * M_PI / 2) || angle < M_PI / 2);
}
