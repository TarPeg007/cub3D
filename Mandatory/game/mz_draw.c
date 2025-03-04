/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:04:52 by mzouine           #+#    #+#             */
/*   Updated: 2025/02/16 13:43:22 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static int	can_move_through(t_map_info *map, int x, int y)
{
	if (map->map[y][x] == '0')
		return (1);
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

void	mz_draw(t_map_info *map)
{
	mz_ray_caster(map);
	map->rotation_angle += map->turn_dir * map->rotation_speed;
	if (map->rotation_angle > (2 * M_PI))
		map->rotation_angle -= (2 * M_PI);
	else if (map->rotation_angle < 0)
		map->rotation_angle += (2 * M_PI);
	map->move_step = map->walk_dir * map->move_speed;
	mz_move_player(map);
}
