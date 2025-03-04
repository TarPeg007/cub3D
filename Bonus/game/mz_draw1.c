/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_draw1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:57:49 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/13 22:43:32 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	update_rotation(t_map_info *map)
{
	map->rotation_angle += map->turn_dir * map->rotation_speed;
	if (map->rotation_angle > (2 * M_PI))
		map->rotation_angle -= (2 * M_PI);
	else if (map->rotation_angle < 0)
		map->rotation_angle += (2 * M_PI);
}

void	mouse_rotate(t_map_info *map)
{
	int			mouse_x;
	int			mouse_y;
	static int	prev_x = -1;
	float		sensitivity;
	int			delta_x;

	sensitivity = 0.0025;
	mlx_get_mouse_pos(map->mlx, &mouse_x, &mouse_y);
	if (prev_x == -1)
		prev_x = mouse_x;
	delta_x = mouse_x - prev_x;
	map->rotation_angle += delta_x * sensitivity;
	update_rotation(map);
	mlx_set_mouse_pos(map->mlx, WIDTH / 2, HEIGHT / 2);
	prev_x = WIDTH / 2;
}

int	is_valid_door_pos(t_map_info *map, int x, int y)
{
	return (x >= 0 && x < map->map_width && y >= 0 && y < map->map_height);
}

void	update_door_state(t_map_info *map, t_door *door, float distance)
{
	if (distance < TILE_SIZE * 2.5)
	{
		if (!door->is_open && map->map[door->y][door->x] == 'D')
		{
			door->is_open = true;
			map->map[door->y][door->x] = '0';
		}
	}
	else if (door->is_open && map->map[door->y][door->x] == '0')
	{
		door->is_open = false;
		map->map[door->y][door->x] = 'D';
	}
}

void	init_line(t_line *line, t_point start, t_point end)
{
	line->x1 = start.x;
	line->y1 = start.y;
	line->dx = fabs(end.x - start.x);
	line->dy = fabs(end.y - start.y);
	if (start.x < end.x)
		line->sx = 1;
	else
		line->sx = -1;
	if (start.y < end.y)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}
