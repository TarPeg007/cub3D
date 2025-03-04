/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:00:05 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/15 16:13:57 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	is_valid_texture_path(char *path)
{
	int		fd;
	char	*trimmed_path;

	if (!path)
		return (0);
	trimmed_path = ft_strtrim(path, " \t\n\r");
	if (!trimmed_path)
		return (0);
	fd = open(trimmed_path, O_RDONLY);
	free(trimmed_path);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	handle_no_so(char *trimmed, t_map_info *info)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && !info->no_texture)
	{
		info->no_texture = ft_strtrim(trimmed + 3, " \n");
		if (!is_valid_texture_path(info->no_texture))
			print_error("Invalid north texture path\n", info);
		return (1);
	}
	if (ft_strncmp(trimmed, "SO ", 3) == 0 && !info->so_texture)
	{
		info->so_texture = ft_strtrim(trimmed + 3, " \n");
		if (!is_valid_texture_path(info->so_texture))
			print_error("Invalid south texture path\n", info);
		return (1);
	}
	return (0);
}

static int	handle_we_ea(char *trimmed, t_map_info *info)
{
	if (ft_strncmp(trimmed, "WE ", 3) == 0 && !info->we_texture)
	{
		info->we_texture = ft_strtrim(trimmed + 3, " \n");
		if (!is_valid_texture_path(info->we_texture))
			print_error("Invalid west texture path\n", info);
		return (1);
	}
	if (ft_strncmp(trimmed, "EA ", 3) == 0 && !info->ea_texture)
	{
		info->ea_texture = ft_strtrim(trimmed + 3, " \n");
		if (!is_valid_texture_path(info->ea_texture))
			print_error("Invalid east texture path\n", info);
		return (1);
	}
	return (0);
}

int	handle_f_c(char *trimmed, t_map_info *info)
{
	if (info->has_error)
		return (0);
	if (ft_strncmp(trimmed, "F ", 2) == 0 && !info->floor_color)
	{
		info->floor_color = ft_strtrim(trimmed + 2, " \n");
		if (!is_valid_rgb(info->floor_color))
		{
			info->has_error = 1;
			ft_putstr_fd("Error\nInvalid floor color\n", 2);
			return (0);
		}
		return (1);
	}
	if (ft_strncmp(trimmed, "C ", 2) == 0 && !info->ceiling_color)
	{
		info->ceiling_color = ft_strtrim(trimmed + 2, " \n");
		if (!is_valid_rgb(info->ceiling_color))
		{
			info->has_error = 1;
			ft_putstr_fd("Error\nInvalid ceiling color\n", 2);
			return (0);
		}
		return (1);
	}
	return (0);
}

int	is_valid_identifier(char *line, t_map_info *info)
{
	char	*trimmed;
	int		ret;

	if (info->has_error)
		return (0);
	trimmed = ft_strtrim(line, " \n");
	ret = 0;
	if (!trimmed)
		return (0);
	ret = handle_no_so(trimmed, info);
	if (!ret && !info->has_error)
		ret = handle_we_ea(trimmed, info);
	if (!ret && !info->has_error)
		ret = handle_f_c(trimmed, info);
	if (ret && !info->has_error)
		info->config_count++;
	free(trimmed);
	return (ret);
}
