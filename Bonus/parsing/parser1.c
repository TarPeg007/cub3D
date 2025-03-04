/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:06:42 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/16 16:41:46 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static int	validate_final(t_map_info *info)
{
	validate_config(info);
	if (info->player_count != 1)
		print_error("Invalid number of players in map\n", info);
	check_map_borders(info);
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

int	valid_map(const char *filename, t_map_info *info)
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

void	set_error(t_map_info *info, char *message)
{
	info->has_error = 1;
	info->error_message = message;
}
