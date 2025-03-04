/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:14:23 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/16 17:08:50 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static void	cleanup_mlx_resources(t_map_info *info)
{
	if (info->mlx)
	{
		if (info->imgg)
			mlx_delete_image(info->mlx, info->imgg);
		if (info->north_img)
			mlx_delete_image(info->mlx, info->north_img);
		if (info->south_img)
			mlx_delete_image(info->mlx, info->south_img);
		if (info->east_img)
			mlx_delete_image(info->mlx, info->east_img);
		if (info->west_img)
			mlx_delete_image(info->mlx, info->west_img);
		if (info->door_img)
			mlx_delete_image(info->mlx, info->door_img);
		mlx_terminate(info->mlx);
	}
}

static void	free_textures(t_map_info *info)
{
	if (info->no_texture)
		free(info->no_texture);
	if (info->so_texture)
		free(info->so_texture);
	if (info->we_texture)
		free(info->we_texture);
	if (info->ea_texture)
		free(info->ea_texture);
	if (info->door_texture)
		free(info->door_texture);
}

static void	free_colors(t_map_info *info)
{
	if (info->floor_color)
		free(info->floor_color);
	if (info->ceiling_color)
		free(info->ceiling_color);
}

static void	free_map_array(t_map_info *info)
{
	int	i;

	if (info->map)
	{
		i = 0;
		while (i < info->map_height)
		{
			if (info->map[i])
				free(info->map[i]);
			i++;
		}
		free(info->map);
	}
}

void	cleanup_map_info(t_map_info *info)
{
	if (!info)
		return ;
	cleanup_mlx_resources(info);
	free_textures(info);
	free_colors(info);
	free_map_array(info);
	if (info->doors)
		free(info->doors);
	if (info->error_message)
		free(info->error_message);
}
