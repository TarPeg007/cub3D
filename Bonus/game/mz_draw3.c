/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_draw3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:01:02 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/13 22:45:16 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	update_ray_position(t_map_info *map, int *pos, int x1, int y1)
{
	if (map->map[y1 / TILE_SIZE][x1 / TILE_SIZE] == '1')
	{
		map->ray_x = x1;
		map->ray_y = y1;
		return (1);
	}
	mlx_put_pixel(map->imgg, x1 + (TILE_SIZE * 6), y1 + (TILE_SIZE * 6),
		pos[2]);
	return (0);
}

void	calc_ray_pos(t_map_info *map, int *pos, int dx, int dy)
{
	int	x1;
	int	y1;
	int	err;
	int	e2;

	x1 = TILE_SIZE * 4;
	y1 = TILE_SIZE * 2;
	err = dx - dy;
	while (1)
	{
		if (update_ray_position(map, pos, x1, y1))
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += pos[0];
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += pos[1];
		}
	}
}

void	mz_draw_minimap(t_map_info *map)
{
	t_point	end;

	mz_draw_minimap_grid(map);
	mz_draw_player(map, (TILE_SIZE / 12) * MINMP_SIZE, 0xFF00FF);
	end.x = (int)(cos(map->rotation_angle) * 50) + (TILE_SIZE * 8);
	end.y = (int)(sin(map->rotation_angle) * 50) + (TILE_SIZE * 4);
	mz_draw_line(map, end, 0x00FFFF);
}

void	mz_draw_line(t_map_info *map, t_point end, int color)
{
	t_line	line;
	t_point	start;

	start.x = TILE_SIZE * 8;
	start.y = TILE_SIZE * 4;
	init_line(&line, start, end);
	draw_pixels(map, &line, end, color);
}
