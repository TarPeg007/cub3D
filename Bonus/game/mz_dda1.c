/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_dda1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:47:00 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/14 17:57:50 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	is_right(float angle)
{
	return (angle >= (3 * M_PI / 2) || angle < M_PI / 2);
}

void	find_wall(t_map_info *data, t_dda *step)
{
	while (1)
	{
		if (is_wall(&data, step->check_pt.x, step->check_pt.y))
			break ;
		step->next.x += step->d_x;
		step->next.y += step->d_y;
		step->check_pt.x += step->d_x;
		step->check_pt.y += step->d_y;
	}
	step->distance = get_distance(data, step->next.x, step->next.y);
}

t_dda	get_hor_inters(t_map_info *data, float angle)
{
	t_dda	step;

	step.next.y = (floor(data->p_y / TILE_SIZE) * TILE_SIZE);
	step.check_pt.y = step.next.y;
	step.d_y = TILE_SIZE;
	if (!is_up(angle))
	{
		step.next.y += TILE_SIZE;
		step.check_pt.y += TILE_SIZE + 1;
	}
	else
	{
		step.d_y *= -1;
		step.check_pt.y -= 1;
	}
	step.next.x = data->p_x + (step.next.y - data->p_y) / tan(angle);
	step.check_pt.x = step.next.x;
	step.d_x = TILE_SIZE / tan(angle);
	if (!is_right(angle) && step.d_x > 0)
		step.d_x *= -1;
	if (is_right(angle) && step.d_x < 0)
		step.d_x *= -1;
	find_wall(data, &step);
	return (step);
}

t_dda	get_vert_inters(t_map_info *data, float angle)
{
	t_dda	step;

	step.next.x = (floor(data->p_x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	step.check_pt.x = step.next.x;
	step.d_x = TILE_SIZE;
	if (!is_right(angle))
	{
		step.next.x -= TILE_SIZE;
		step.check_pt.x -= (TILE_SIZE + 1);
		step.d_x *= -1;
	}
	else
		step.check_pt.x += 1;
	step.next.y = data->p_y + (step.next.x - data->p_x) * tan(angle);
	step.check_pt.y = step.next.y;
	step.d_y = TILE_SIZE * tan(angle);
	if (is_up(angle) && step.d_y > 0)
		step.d_y *= -1;
	if (!is_up(angle) && step.d_y < 0)
		step.d_y *= -1;
	return (find_wall(data, &step), step);
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
