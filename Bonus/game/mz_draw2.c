/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_draw2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:53:37 by sfellahi          #+#    #+#             */
/*   Updated: 2025/03/02 16:52:43 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	handle_doors(t_map_info *map)
{
	int		i;
	float	door_center_x;
	float	door_center_y;
	float	distance;

	if (!map || !map->doors || map->door_count <= 0)
		return ;
	i = 0;
	while (i < map->door_count)
	{
		if (!is_valid_door_pos(map, map->doors[i].x, map->doors[i].y))
		{
			i++;
			continue ;
		}
		door_center_x = map->doors[i].x * TILE_SIZE + (TILE_SIZE / 2);
		door_center_y = map->doors[i].y * TILE_SIZE + (TILE_SIZE / 2);
		distance = sqrt(pow(map->p_x - door_center_x, 2)
				+ pow(map->p_y - door_center_y, 2));
		update_door_state(map, &map->doors[i], distance);
		i++;
	}
}

void	mz_draw_ray(t_map_info *map, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	pos[3];

	dx = abs(x2 - (TILE_SIZE * 4));
	dy = abs(y2 - (TILE_SIZE * 2));
	if ((TILE_SIZE * 4) < x2)
		pos[0] = 1;
	else
		pos[0] = -1;
	if ((TILE_SIZE * 2) < y2)
		pos[1] = 1;
	else
		pos[1] = -1;
	pos[2] = color;
	calc_ray_pos(map, pos, dx, dy);
}

void	mz_draw_player(t_map_info *map, int radius, int color)
{
	int	i;
	int	x1;
	int	y1;
	int	angle;

	i = -1;
	while (i < 359)
	{
		i++;
		angle = i;
		x1 = radius * cos(angle * M_PI / 180);
		y1 = radius * sin(angle * M_PI / 180);
		if (angle == 0 || angle == 90 || angle == 180 || angle == 270)
			continue ;
		mlx_put_pixel(map->imgg, ((TILE_SIZE * 8) + x1) / MINMP_SIZE,
			((TILE_SIZE * 4) + y1) / MINMP_SIZE, color);
	}
}
