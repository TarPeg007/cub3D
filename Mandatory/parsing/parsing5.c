/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:10:14 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/14 11:15:34 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
	Ensuring strings do not contain trailing newlines before further processing.
	This checks if the last character in cleaned_line is a newline (\n).
	If so, it replaces it with the null terminator (\0), effectively removing it.
	This ensures that the returned string does not end with a newline. ;)
		{TarPeg007}
*/

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

int	is_valid_rgb(char *str)
{
	char	**colors;
	int		ret;

	if (!check_commas(str))
		return (0);
	colors = ft_split(str, ',');
	if (!colors)
		return (0);
	ret = validate_color_range(colors);
	ft_free_array(colors);
	return (ret);
}
