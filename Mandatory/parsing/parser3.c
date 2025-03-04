/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:10:08 by sfellahi          #+#    #+#             */
/*   Updated: 2025/03/02 15:24:52 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static int	process_file_lines(int fd, t_map_info *info, int *map_started)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && !info->has_error)
	{
		if (!handle_line(line, info, map_started))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

static int	handle_file_open(const char *filename, t_map_info *info, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		set_error(info, "Cannot open map file\n");
		return (0);
	}
	return (1);
}

int	valid_map(char *filename, t_map_info *info)
{
	int		fd;
	int		map_started;
	int		result;

	init_map_info(info);
	if (!handle_file_open(filename, info, &fd))
		return (0);
	map_started = 0;
	if (!process_file_lines(fd, info, &map_started))
	{
		close(fd);
		cleanup_map_info(info);
		return (0);
	}
	close(fd);
	result = validate_final(info);
	if (!result || info->has_error)
	{
		ft_putstr_fd("Error\n", 2);
		if (info->error_message)
			ft_putstr_fd(info->error_message, 2);
		cleanup_map_info(info);
		return (0);
	}
	return (1);
}

void	check_horizontal_borders(t_map_info *info, int max_len)
{
	int	j;

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
