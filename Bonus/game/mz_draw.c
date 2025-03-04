/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:04:52 by mzouine           #+#    #+#             */
/*   Updated: 2025/02/13 15:35:24 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static int	can_move_through(t_map_info *map, int x, int y)
{
	int	i;

	if (map->map[y][x] == '0')
		return (1);
	if (map->map[y][x] == 'D')
	{
		i = 0;
		while (i < map->door_count)
		{
			if (map->doors[i].x == x && map->doors[i].y == y)
				return (map->doors[i].is_open);
			i++;
		}
	}
	return (0);
}

void	check_move(t_map_info *map, float *move)
{
	int	check_y;
	int	check_x;

	check_y = (int)round(map->p_y) / TILE_SIZE;
	check_x = ((int)round(map->p_x + move[0]) + 8) / TILE_SIZE;
	if (move[0] > 0 && can_move_through(map, check_x, check_y))
		map->p_x += move[0];
	else if (move[0] < 0 && (map->map[(int)round(map->p_y) / TILE_SIZE]
			[((int)round(map->p_x + move[0]) - 8) / TILE_SIZE] == '0'))
		map->p_x += move[0];
	if (move[1] > 0 && map->map[((int)round(map->p_y + move[1]) + 8)
			/ TILE_SIZE][(int)round(map->p_x) / TILE_SIZE] == '0')
		map->p_y += move[1];
	else if (move[1] < 0 && map->map[((int)round(map->p_y + move[1]) - 8)
			/ TILE_SIZE][(int)round(map->p_x) / TILE_SIZE] == '0')
		map->p_y += move[1];
}

void	mz_move_player(t_map_info *map)
{
	float	move[2];

	move[0] = 0;
	move[1] = 0;
	if (map->walk_dir != 0)
	{
		move[0] += cos(map->rotation_angle) * map->move_step;
		move[1] += sin(map->rotation_angle) * map->move_step;
	}
	if (map->strafe_dir != 0)
	{
		move[0] += cos(map->rotation_angle + M_PI / 2)
			* (map->strafe_dir * map->move_speed);
		move[1] += sin(map->rotation_angle + M_PI / 2)
			* (map->strafe_dir * map->move_speed);
	}
	check_move(map, move);
}

void	mz_draw_minimap_pixel(t_map_info *map, int i, int j, int *coords)
{
	int	color;

	color = 0xFF000000;
	if (j < 0 || (j >= map->map_height * TILE_SIZE)
		|| i < 0 || (i >= map->map_width * TILE_SIZE))
		color = 0xFF000000;
	else if (map->map[j / TILE_SIZE][i / TILE_SIZE] == '0')
		color = 0xFFFFFFFF;
	else if (map->map[j / TILE_SIZE][i / TILE_SIZE] == 'D')
		color = 0xFFFF00FF;
	mlx_put_pixel(map->imgg, coords[0]
		/ MINMP_SIZE, coords[1] / MINMP_SIZE, color);
}

void	mz_draw_minimap_grid(t_map_info *map)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	coords[2];

	j = map->p_y - (TILE_SIZE * 4);
	y = 0;
	while (j < map->p_y + (TILE_SIZE * 4))
	{
		i = map->p_x - (TILE_SIZE * 8);
		x = 0;
		while (i < map->p_x + (TILE_SIZE * 8))
		{
			coords[0] = x;
			coords[1] = y;
			mz_draw_minimap_pixel(map, i, j, coords);
			i += MINMP_SIZE;
			x += MINMP_SIZE;
		}
		j += MINMP_SIZE;
		y += MINMP_SIZE;
	}
}
