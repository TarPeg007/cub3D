/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:45:39 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/13 22:27:54 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

size_t	get_max_len(t_map_info *info)
{
	int		i;
	size_t	max_len;

	max_len = 0;
	i = 0;
	while (i < info->map_height)
	{
		max_len = ft_max(max_len, ft_strlen(info->map[i]));
		i++;
	}
	return (max_len);
}

void	check_horizontal_borders(t_map_info *info, size_t max_len)
{
	size_t	j;

	j = 0;
	while (j < max_len)
	{
		if (j < ft_strlen(info->map[0]) && info->map[0][j] != '1'
			&& info->map[0][j] != ' ')
			print_error("Map must be surrounded by 1 (top border)\n", info);
		if (j < ft_strlen(info->map[info->map_height - 1])
			&& info->map[info->map_height - 1][j] != '1'
			&& info->map[info->map_height - 1][j] != ' ')
			print_error("Map must be surrounded by 1 (bottom border)\n", info);
		j++;
	}
}

int	validate_door(t_map_info *info, int i, size_t j, size_t len)
{
	if (j > 0 && j < len - 1 && info->map[i][j - 1] == '1'
		&& info->map[i][j + 1] == '1')
		return (1);
	if (i > 0 && i < info->map_height - 1
		&& j < ft_strlen(info->map[i - 1])
		&& j < ft_strlen(info->map[i + 1])
		&& info->map[i - 1][j] == '1'
		&& info->map[i + 1][j] == '1')
		return (1);
	return (0);
}

void	check_surroundings(t_map_info *info, int i, size_t j, size_t len)
{
	if (i > 0 && (j >= ft_strlen(info->map[i - 1])
			|| info->map[i - 1][j] == ' '))
		print_error("Map must be properly closed (top)\n", info);
	if (i < info->map_height - 1
		&& (j >= ft_strlen(info->map[i + 1])
			|| info->map[i + 1][j] == ' '))
		print_error("Map must be properly closed (bottom)\n", info);
	if (j > 0 && info->map[i][j - 1] == ' ')
		print_error("Map must be properly closed (left)\n", info);
	if (j < len - 1 && info->map[i][j + 1] == ' ')
		print_error("Map must be properly closed (right)\n", info);
	if (info->map[i][j] == 'D' && !validate_door(info, i, j, len))
		print_error("Doors must be placed between walls\n", info);
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
