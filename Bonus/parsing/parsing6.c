/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:35:27 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/16 16:14:50 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	process_line_characters(char *clean_line, t_map_info *info, int height)
{
	int	i;

	i = -1;
	while (clean_line[++i] && !info->has_error)
	{
		if (ft_strchr("NSEW", clean_line[i]))
			handle_player_position(clean_line[i], i, info, height);
		else if (clean_line[i] == 'D')
			handle_door_position(i, info, height);
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
	ft_putstr_fd("Memory allocation failed for map line\n", 2);
}

void	update_map_info(t_map_info *info, char **new_map, char *cleaned_line)
{
	free(info->map);
	info->map = new_map;
	info->map_height++;
	info->map_width = ft_max(info->map_width, ft_strlen(cleaned_line));
}

void	process_map_line(char *line, t_map_info *info)
{
	char	**new_map;
	char	*cleaned_line;

	if (info->has_error)
		return ;
	cleaned_line = clean_line(line, info);
	new_map = allocate_new_map(info, cleaned_line);
	if (!new_map)
	{
		free(cleaned_line);
		info->has_error = 1;
		return ;
	}
	copy_existing_map(new_map, info);
	new_map[info->map_height] = ft_strdup(cleaned_line);
	if (!new_map[info->map_height])
	{
		handle_allocation_error(info, cleaned_line, new_map, info->map_height);
		return ;
	}
	new_map[info->map_height + 1] = NULL;
	update_map_info(info, new_map, cleaned_line);
	process_line_characters(cleaned_line, info, info->map_height - 1);
	free(cleaned_line);
}

void	validate_map_chars(t_map_info *info, int i, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (info->map[i][j] != ' ')
		{
			if (!ft_strchr("01NSEWDC", info->map[i][j]))
				print_error("Invalid character in map\n", info);
			if (ft_strchr("0NSEWDC", info->map[i][j]))
				check_surroundings(info, i, j, len);
		}
		j++;
	}
}
