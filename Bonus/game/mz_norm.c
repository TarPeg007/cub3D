/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:43:55 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/13 22:44:41 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	draw_pixels(t_map_info *map, t_line *line, t_point end, int color)
{
	while (1)
	{
		mlx_put_pixel(map->imgg, line->x1 / MINMP_SIZE,
			line->y1 / MINMP_SIZE, color);
		if (line->x1 == end.x && line->y1 == end.y)
			break ;
		line->e2 = line->err * 2;
		if (line->e2 > -line->dy)
		{
			line->err -= line->dy;
			line->x1 += line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err += line->dx;
			line->y1 += line->sy;
		}
	}
}
