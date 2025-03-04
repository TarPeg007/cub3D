/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:13:16 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/20 11:54:47 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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
		return (NULL);
	}
	return (map);
}

void	validate_map_chars(t_map_info *info, int i, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (info->map[i][j] != ' ')
		{
			if (!ft_strchr("01NSEW", info->map[i][j]))
				print_error("Invalid character in map\n", info);
			if (ft_strchr("0NSEW", info->map[i][j]))
				check_surroundings(info, i, j, len);
		}
		j++;
	}
}

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
	info->p_y = height * TILE_SIZE + (TILE_SIZE / 2);
	info->p_orient = c;
}

void	process_line_characters(char *clean_line, t_map_info *info, int height)
{
	int	i;

	i = -1;
	while (clean_line[++i] && !info->has_error)
	{
		if (ft_strchr("NSEW", clean_line[i]))
			handle_player_position(clean_line[i], i, info, height);
	}
}
