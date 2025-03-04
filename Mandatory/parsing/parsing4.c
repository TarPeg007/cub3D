/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:02:27 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/17 16:11:27 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_map_info(t_map_info *info)
{
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->floor_color = NULL;
	info->ceiling_color = NULL;
	info->map = NULL;
	info->map_height = 0;
	info->map_width = 0;
	info->player_count = 0;
	info->config_count = 0;
	info->parsing_map = 0;
	info->error_message = NULL;
	info->mlx = NULL;
	info->north = NULL;
	info->south = NULL;
	info->east = NULL;
	info->west = NULL;
	info->north_img = NULL;
	info->south_img = NULL;
	info->east_img = NULL;
	info->west_img = NULL;
	info->imgg = NULL;
}

void	check_vertical_borders(t_map_info *info, int i, size_t len)
{
	if (info->map[i][0] != '1' && info->map[i][0] != ' ')
		print_error("Map must be surrounded by walls (left border)\n", info);
	if (info->map[i][len - 1] != '1' && info->map[i][len - 1] != ' ')
		print_error("Map must be surrounded by walls (right border)\n", info);
}

void	check_map_borders(t_map_info *info)
{
	int		i;
	size_t	len;
	size_t	max_len;

	max_len = get_max_len(info);
	check_horizontal_borders(info, max_len);
	i = 0;
	while (i < info->map_height)
	{
		len = ft_strlen(info->map[i]);
		check_vertical_borders(info, i, len);
		validate_map_chars(info, i, len);
		i++;
	}
}

void	handle_allocation_error(t_map_info *info, char *cleaned_line,
			char **new_map, int height)
{
	int	i;

	free(cleaned_line);
	i = 0;
	while (i < height)
	{
		if (new_map[i] != info->map[i])
			free(new_map[i]);
		i++;
	}
	free(new_map);
	info->has_error = 1;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Memory allocation failed for map line\n", 2);
}

void	update_map_info(t_map_info *info, char **new_map, char *cleaned_line)
{
	free(info->map);
	info->map = new_map;
	info->map_height++;
	info->map_width = ft_max(info->map_width, ft_strlen(cleaned_line));
}
