/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:46:44 by mzouine           #+#    #+#             */
/*   Updated: 2025/02/14 17:57:34 by sfellahi         ###   ########.fr       */
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

int	calculate_tex_x(t_ray *ray, mlx_image_t *current_texture)
{
	int		tex_x;
	float	hit_offset;

	if (ray->direction == DOOR && current_texture)
	{
		if (ray->is_ver)
			hit_offset = fmod(ray->end_y, TILE_SIZE);
		else
			hit_offset = fmod(ray->end_x, TILE_SIZE);
		tex_x = (int)((hit_offset / TILE_SIZE) * current_texture->width);
		if (ray->door_qa)
			tex_x = current_texture->width - tex_x - 1;
		tex_x = fmax(0, fmin(tex_x, current_texture->width - 1));
		return (tex_x);
	}
	if (ray->direction == EAST || ray->direction == WEST)
		tex_x = (int)(fmod(ray->end_y, TILE_SIZE)
				* ((float)current_texture->width / TILE_SIZE));
	else
		tex_x = (int)(fmod(ray->end_x, TILE_SIZE)
				* ((float)current_texture->width / TILE_SIZE));
	return (tex_x);
}

void	render_wall_section(t_render_data *r_data, int y)
{
	float		tex_y_ratio;
	uint32_t	color;

	tex_y_ratio = (y - r_data->wall_top)
		/ (r_data->wall_bottom - r_data->wall_top);
	r_data->tex_y = (int)(tex_y_ratio
			* r_data->current_texture->height);
	r_data->tex_y = fmin(r_data->tex_y,
			r_data->current_texture->height - 1);
	color = get_shaded_texture_color(r_data->current_texture,
			r_data->tex_x, r_data->tex_y);
	mlx_put_pixel(r_data->data->imgg, r_data->x, y, color);
}

void	mz_render(t_render_data *r_data)
{
	int			y;
	mlx_image_t	*current_texture;

	y = 0;
	r_data->data->ceiling_color_int
		= parse_rgb_string(r_data->data->ceiling_color);
	r_data->data->floor_color_int
		= parse_rgb_string(r_data->data->floor_color);
	select_texture(r_data->data, r_data->ray, &current_texture);
	r_data->current_texture = current_texture;
	r_data->tex_x = calculate_tex_x(r_data->ray, current_texture);
	while (y < r_data->wall_top && y < HEIGHT)
		mlx_put_pixel(r_data->data->imgg, r_data->x, y++,
			r_data->data->ceiling_color_int);
	while (y < r_data->wall_bottom && y < HEIGHT)
		render_wall_section(r_data, y++);
	while (y < HEIGHT)
		mlx_put_pixel(r_data->data->imgg, r_data->x, y++,
			r_data->data->floor_color_int);
}
