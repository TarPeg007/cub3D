/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:10:11 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/16 16:13:03 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	handle_player_position(char c, int x, t_map_info *info, int height)
{
	info->player_count++;
	if (info->player_count > 1 && !info->has_error)
	{
		info->has_error = 1;
		ft_putstr_fd("Error\nMultiple player Or Double path\n", 2);
		return ;
	}
	info->p_x = x * TILE_SIZE + (TILE_SIZE / 2);
	info->p_y = (height) * TILE_SIZE + (TILE_SIZE / 2);
	info->p_orient = c;
}

void	handle_door_position(int x, t_map_info *info, int height)
{
	t_door	*new_doors;

	new_doors = realloc(info->doors, sizeof(t_door) * (info->door_count + 1));
	if (!new_doors)
		print_error("Memory allocation failed for doors\n", info);
	info->doors = new_doors;
	info->doors[info->door_count].x = x;
	info->doors[info->door_count].y = height;
	info->doors[info->door_count].is_open = 0;
	info->door_count++;
}

char	*clean_line(char *line, t_map_info *info)
{
	char	*cleaned_line;

	cleaned_line = ft_strdup(line);
	if (!cleaned_line)
		print_error("Memory allocation failed\n", info);
	if (cleaned_line[ft_strlen(cleaned_line) - 1] == '\n')
		cleaned_line[ft_strlen(cleaned_line) - 1] = '\0';
	return (cleaned_line);
}

char	**allocate_new_map(t_map_info *info, char *cleaned_line)
{
	char	**new_map;

	new_map = malloc(sizeof(char *) * (info->map_height + 2));
	if (!new_map)
	{
		free(cleaned_line);
		print_error("Memory allocation failed for map\n", info);
	}
	return (new_map);
}

void	copy_existing_map(char **new_map, t_map_info *info)
{
	int	i;

	i = -1;
	while (++i < info->map_height)
		new_map[i] = info->map[i];
}
