/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:06:27 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/26 20:49:39 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	check_args(int argc, char *argv[])
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

t_map_info	*allocate_map(void)
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
	map->map_height = 0;
	map->map_width = 0;
	map->player_count = 0;
	map->has_error = 0;
	map->config_count = 0;
	return (map);
}

// Fixed the exit and free if malloc failed or error happened ;)