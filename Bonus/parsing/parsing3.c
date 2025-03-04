/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:37:46 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/18 12:51:00 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static void	init_texture_info(t_map_info *info)
{
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->door_texture = NULL;
	info->mlx = NULL;
	info->imgg = NULL;
	info->north = NULL;
	info->south = NULL;
	info->east = NULL;
	info->west = NULL;
	info->north_img = NULL;
	info->south_img = NULL;
	info->east_img = NULL;
	info->west_img = NULL;
	info->door_img = NULL;
}

void	init_map_info(t_map_info *info)
{
	info->map = NULL;
	info->map_height = 0;
	info->map_width = 0;
	info->player_count = 0;
	info->config_count = 0;
	info->parsing_map = 0;
	info->floor_color = NULL;
	info->ceiling_color = NULL;
	info->doors = NULL;
	info->door_count = 0;
	info->ray.door_qa = 0;
	info->error_message = NULL;
	init_texture_info(info);
}

static void	check_args(int argc, char *argv[])
{
	size_t	len;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid arguments.\n", 2);
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid File Extension.\n", 2);
		exit(1);
	}
}

static t_map_info	*allocate_map(void)
{
	t_map_info	*map;

	map = malloc(sizeof(t_map_info));
	if (!map)
	{
		ft_putstr_fd("Error\nMemory allocation failed.\n", 2);
		exit(1);
	}
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->map = NULL;
	map->doors = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->door_count = 0;
	map->player_count = 0;
	map->has_error = 0;
	map->config_count = 0;
	return (map);
}

t_map_info	*parser(int argc, char *argv[])
{
	t_map_info	*map;

	check_args(argc, argv);
	map = allocate_map();
	if (!map)
		return (NULL);
	if (!valid_map(argv[1], map))
	{
		free(map);
		exit(1);
	}
	return (map);
}
