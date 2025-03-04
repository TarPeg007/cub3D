/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:02:56 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/16 14:19:48 by sfellahi         ###   ########.fr       */
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
		map->move_speed = TILE_SIZE / 3;
	if (!mlx_is_key_down(map->mlx, MLX_KEY_LEFT_SHIFT))
		map->move_speed = TILE_SIZE / 17;
}

float	normalize_angle(float angle)
{
	float	normalized;

	normalized = fmod(angle, 2 * M_PI);
	if (normalized < 0.0)
		normalized += 2 * M_PI;
	return (normalized);
}
