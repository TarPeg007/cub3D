/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:51:54 by sfellahi          #+#    #+#             */
/*   Updated: 2025/03/01 20:30:41 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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
