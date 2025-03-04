/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:00:05 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/16 16:15:41 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	validate_config(t_map_info *info)
{
	if (!info->no_texture || !info->so_texture || !info->we_texture
		|| !info->ea_texture || !info->floor_color || !info->ceiling_color)
		print_error("Missing configuration elements\n", info);
}

static int	handle_empty_line(char *line, t_map_info *info, int *map_started)
{
	if (*map_started && ft_strlen(line) <= 1)
	{
		info->has_error = 1;
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Empty line within map content or double F C\n", 2);
		return (0);
	}
	return (1);
}

static void	start_map_parsing(t_map_info *info, int *map_started, char *line)
{
	info->parsing_map = 1;
	*map_started = 1;
	process_map_line(line, info);
}

int	handle_line(char *line, t_map_info *info, int *map_started)
{
	if (!*map_started && ft_strlen(line) <= 1)
		return (1);
	if (!info->parsing_map && info->config_count < 6)
	{
		if (!is_valid_identifier(line, info) && ft_strlen(line) > 1)
			start_map_parsing(info, map_started, line);
		return (!info->has_error);
	}
	if (ft_strlen(line) > 1 || info->parsing_map)
	{
		if (!handle_empty_line(line, info, map_started))
			return (0);
		start_map_parsing(info, map_started, line);
		return (!info->has_error);
	}
	return (1);
}

void	check_vertical_borders(t_map_info *info, int i, size_t len)
{
	if (info->map[i][0] != '1' && info->map[i][0] != ' ')
		print_error("Map must be surrounded by walls (left border)\n", info);
	if (info->map[i][len - 1] != '1' && info->map[i][len - 1] != ' ')
		print_error("Map must be surrounded by walls (right border)\n", info);
}
