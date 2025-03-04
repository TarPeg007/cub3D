/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:51:09 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/14 13:09:46 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*create_weapon_path(t_map_info *map, char *path)
{
	char	*name;
	char	*number;
	char	*full_path;

	number = ft_itoa(map->gun->current_frame);
	if (!number)
		print_error("Error: malloc failed\n", map);
	name = safe_strjoin(path, number, map);
	free(number);
	if (!name)
		print_error("Error: malloc failed\n", map);
	full_path = safe_strjoin(name, ".png", map);
	free(name);
	if (!full_path)
		print_error("Error: malloc failed\n", map);
	return (full_path);
}

mlx_image_t	*create_weapon_image(t_map_info *map, char *full_path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*cur_img;

	texture = mlx_load_png(full_path);
	free(full_path);
	if (!texture)
		print_error("Error: Failed to load texture122\n", map);
	cur_img = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	if (!cur_img)
		print_error("Error: Failed to create image\n", map);
	if (mlx_image_to_window(map->mlx, cur_img, WEAPON_X, WEAPON_Y) < 0)
		print_error("Error: Failed to add image to window\n", map);
	return (cur_img);
}

void	update_weapon_state(t_map_info *map, int max_frames)
{
	map->gun->current_frame++;
	if (map->gun->current_frame >= max_frames)
	{
		map->gun->current_frame = 0;
		map->gun->init_state = true;
		map->gun->is_shooting = false;
		map->gun->is_reloading = false;
		map->gun->is_zooming = false;
	}
}

void	update_gun_animation(t_map_info *map)
{
	static mlx_image_t	*prev_img = NULL;

	if (!map->gun)
		return ;
	map->gun->frame_counter++;
	if (map->gun->frame_counter >= 1)
	{
		if (prev_img)
		{
			mlx_delete_image(map->mlx, prev_img);
			prev_img = NULL;
		}
		prev_img = play_weapon(map);
		map->gun->frame_counter = 0;
	}
}

void	handle_gun_action(t_map_info *map, int action)
{
	if (action == 1 && map->gun->init_state)
	{
		map->gun->is_shooting = true;
		map->gun->init_state = false;
		map->gun->current_frame = 0;
		map->sound->play_shoot = 1;
	}
	else if (action == 2 && map->gun->init_state)
	{
		map->gun->is_reloading = true;
		map->gun->init_state = false;
		map->gun->current_frame = 0;
		map->sound->play_reload = 1;
	}
	else if (action == 3 && map->gun->init_state)
	{
		map->gun->is_zooming = true;
		map->gun->init_state = false;
		map->gun->current_frame = 0;
	}
}
