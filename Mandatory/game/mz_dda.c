/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:46:44 by mzouine           #+#    #+#             */
/*   Updated: 2025/03/02 16:06:18 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

uint32_t	parse_rgb_components(char **colors)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	return (get_rgba(r, g, b, 255));
}

uint32_t	parse_rgb_string(char *rgb_str)
{
	char		**colors;
	uint32_t	color;
	int			i;

	colors = ft_split(rgb_str, ',');
	if (!colors)
		return (0xFF000000);
	color = parse_rgb_components(colors);
	i = 0;
	while (colors[i])
		free(colors[i++]);
	free(colors);
	return (color);
}

void	select_texture(t_map_info *data, t_ray *ray,
		mlx_image_t **current_texture)
{
	*current_texture = NULL;
	if (ray->direction == NORTH && data->north_img)
		*current_texture = data->north_img;
	else if (ray->direction == SOUTH && data->south_img)
		*current_texture = data->south_img;
	else if (ray->direction == EAST && data->east_img)
		*current_texture = data->east_img;
	else if (ray->direction == WEST && data->west_img)
		*current_texture = data->west_img;
}
/*
For example, if TILE_SIZE is 64 and 
ray->end_y is 385, then fmod(385, 64) = 1, 
meaning the ray hit 1 pixel into the tile

For example, if TILE_SIZE is 64 and 
ray->end_y is 385, then fmod(385, 64) = 1,
 meaning the ray hit 1 pixel into the tile
*/

int	calculate_tex_x(t_ray *ray, mlx_image_t *current_texture)
{
	int		tex_x;

	if (ray->direction == EAST || ray->direction == WEST)
		tex_x = (int)(fmod(ray->end_y, TILE_SIZE)
				* ((float)current_texture->width / TILE_SIZE));
	else
		tex_x = (int)(fmod(ray->end_x, TILE_SIZE)
				* ((float)current_texture->width / TILE_SIZE));
	tex_x = fmax(0, fmin(tex_x, current_texture->width - 1));
	return (tex_x);
}

uint32_t	get_shaded_texture_color(mlx_image_t *texture, int tex_x, int tex_y)
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	color = ((uint32_t *)texture->pixels)[tex_y * texture->width + tex_x];
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	a = (color >> 24) & 0xFF;
	return (get_rgba(b, g, r, a));
}
