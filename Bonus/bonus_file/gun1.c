/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:10:16 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/12 10:38:29 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_gun(t_map_info *map)
{
	map->gun = malloc(sizeof(t_gun));
	if (!map->gun)
		print_error("Error: Failed to allocate memory for gun\n", map);
	ft_memset(map->gun, 0, sizeof(t_gun));
	map->gun->is_shooting = false;
	map->gun->is_reloading = false;
	map->gun->is_zooming = false;
	map->gun->current_frame = 0;
	map->gun->init_state = true;
	map->gun->frame_counter = 0;
}

mlx_image_t	*play_init_state(t_map_info *map)
{
	char			*name;
	mlx_image_t		*cur_img;
	mlx_texture_t	*texture;

	name = ft_strdup(PATH_WEAPON_INIT_STATE);
	if (!name)
		print_error("Error: malloc failed\n", map);
	texture = mlx_load_png(name);
	if (!texture)
	{
		free(name);
		print_error("Error: Failed to load texture\n", map);
	}
	cur_img = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	free(name);
	if (!cur_img)
		print_error("Error: Failed to create image\n", map);
	mlx_image_to_window(map->mlx, cur_img, WEAPON_X, WEAPON_Y);
	return (cur_img);
}

char	*safe_strjoin(char *s1, char *s2, t_map_info *map)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		print_error("Error: malloc failed\n", map);
	}
	ft_memset(result, 0, len1 + len2 + 1);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}
