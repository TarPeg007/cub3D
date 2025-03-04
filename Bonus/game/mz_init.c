/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:07:17 by mzouine           #+#    #+#             */
/*   Updated: 2025/02/11 10:51:10 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static void	mz_find_player(t_map_info *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == 'N' || map->map[j][i] == 'S'
				|| map->map[j][i] == 'E' || map->map[j][i] == 'W')
			{
				map->p_x = (i * TILE_SIZE) + (TILE_SIZE / 2);
				map->p_y = (j * TILE_SIZE) + (TILE_SIZE / 2);
				map->p_orient = map->map[j][i];
				map->map[j][i] = '0';
				return ;
			}
			i++;
		}
		j++;
	}
}

void	mz_init_player(t_map_info *map)
{
	mz_find_player(map);
	map->turn_dir = 0;
	map->walk_dir = 0;
	map->strafe_dir = 0;
	if (map->p_orient == 'N')
		map->rotation_angle = (M_PI / 2) * -1;
	else if (map->p_orient == 'E')
		map->rotation_angle = (0) * -1;
	else if (map->p_orient == 'W')
		map->rotation_angle = (M_PI) * -1;
	else if (map->p_orient == 'S')
		map->rotation_angle = ((3 * M_PI) / 2) * -1;
	map->move_step = 0;
	map->move_speed = TILE_SIZE / 18;
	map->rotation_speed = mz_deg2rad(4);
}

void	mz_draw(t_map_info *map)
{
	map->ray.is_a_door = 0;
	mz_ray_caster(map);
	mz_draw_minimap(map);
	handle_doors(map);
	mouse_rotate(map);
	update_gun_animation(map);
	handle_gun_shooting(map);
	render_crosshair(map);
	update_rotation(map);
	map->move_step = map->walk_dir * map->move_speed;
	mz_move_player(map);
}
