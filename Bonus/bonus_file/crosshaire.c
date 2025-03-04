/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:59:21 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/12 10:40:15 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static void	draw_horizontal_line(t_crosshair *ch, int center, int gap)
{
	int	x;
	int	t;
	int	y;

	x = 0;
	while (x < ch->size)
	{
		if (abs(x - center) <= gap)
		{
			x++;
			continue ;
		}
		t = 0;
		while (t < ch->thickness)
		{
			y = center + t - ch->thickness / 2;
			if (y >= 0 && y < ch->size)
				mlx_put_pixel(ch->image, x, y, ch->color);
			t++;
		}
		x++;
	}
}

static void	draw_vertical_line(t_crosshair *ch, int center, int gap)
{
	int	y;
	int	t;
	int	x;

	y = 0;
	while (y < ch->size)
	{
		if (abs(y - center) <= gap)
		{
			y++;
			continue ;
		}
		t = 0;
		while (t < ch->thickness)
		{
			x = center + t - ch->thickness / 2;
			if (x >= 0 && x < ch->size)
				mlx_put_pixel(ch->image, x, y, ch->color);
			t++;
		}
		y++;
	}
}

void	init_crosshair(t_map_info *map)
{
	int	center;
	int	gap;

	map->crosshair = malloc(sizeof(t_crosshair));
	if (!map->crosshair)
		print_error("Error: Failed to allocate memory for crosshair\n", map);
	map->crosshair->size = 30;
	map->crosshair->thickness = 3;
	map->crosshair->color = 0xFF0000FF;
	map->crosshair->image = mlx_new_image(map->mlx,
			map->crosshair->size, map->crosshair->size);
	if (!map->crosshair->image)
	{
		free(map->crosshair);
		print_error("Error: Failed to create crosshair image\n", map);
	}
	center = map->crosshair->size / 2;
	gap = 2;
	draw_horizontal_line(map->crosshair, center, gap);
	draw_vertical_line(map->crosshair, center, gap);
}

void	render_crosshair(t_map_info *map)
{
	int	x;
	int	y;

	if (!map->crosshair || !map->crosshair->image)
		return ;
	x = (WIDTH - map->crosshair->size) / 2;
	y = (HEIGHT - map->crosshair->size) / 2;
	mlx_image_to_window(map->mlx, map->crosshair->image, x, y);
}

void	cleanup_crosshair(t_map_info *map)
{
	if (map->crosshair)
	{
		if (map->crosshair->image)
			mlx_delete_image(map->mlx, map->crosshair->image);
		free(map->crosshair);
		map->crosshair = NULL;
	}
}
