/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:43:12 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/12 10:47:58 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	handle_gun_shooting(t_map_info *map)
{
	if (!map->gun)
		return ;
	if (mlx_is_mouse_down(map->mlx, MLX_MOUSE_BUTTON_LEFT))
		handle_gun_action(map, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_R))
		handle_gun_action(map, 2);
	if (mlx_is_mouse_down(map->mlx, MLX_MOUSE_BUTTON_RIGHT))
		handle_gun_action(map, 3);
}

void	cleanup_gun(t_map_info *map)
{
	if (!map->gun)
		return ;
	free(map->gun);
	map->gun = NULL;
}

mlx_image_t	*play_weapon_status(t_map_info *map, int max_frames, char *path)
{
	char		*full_path;
	mlx_image_t	*cur_img;

	full_path = create_weapon_path(map, path);
	cur_img = create_weapon_image(map, full_path);
	update_weapon_state(map, max_frames);
	return (cur_img);
}

mlx_image_t	*play_weapon(t_map_info *map)
{
	mlx_image_t	*cur_img;

	cur_img = NULL;
	if (map->gun->is_reloading)
		cur_img = play_weapon_status(map, FRAMES_RELOAD, PATH_WEAPON_RELOAD);
	else if (map->gun->init_state)
	{
		cur_img = play_init_state(map);
		map->gun->current_frame = 0;
	}
	else if (map->gun->is_shooting)
		cur_img = play_weapon_status(map, FRAMES_SHOOT,
				PATH_WEAPON_NORMAL_SHOOT);
	else if (map->gun->is_zooming)
		cur_img = play_weapon_status(map, FRAMES_ZOOM, PATH_WEAPON_ZOOM_SHOOT);
	return (cur_img);
}
