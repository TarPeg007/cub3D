/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:50:55 by mzouine           #+#    #+#             */
/*   Updated: 2025/02/24 10:10:13 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static void	load_texture_files(t_map_info *data)
{
	data->north = mlx_load_png(data->no_texture);
	data->south = mlx_load_png(data->so_texture);
	data->east = mlx_load_png(data->ea_texture);
	data->west = mlx_load_png(data->we_texture);
	if (!data->north || !data->south || !data->east || !data->west)
	{
		ft_putstr_fd("Error\nFailed to load textures\n", 2);
		cleanup_map_info(data);
		exit(1);
	}
	data->door_texture = mlx_load_png("Bonus/textures/door.png");
	if (!data->door_texture)
	{
		ft_putstr_fd("Error\nFailed to load door texture\n", 2);
		cleanup_map_info(data);
		exit(1);
	}
}

static void	convert_textures_to_images(t_map_info *data)
{
	data->north_img = mlx_texture_to_image(data->mlx, data->north);
	mlx_delete_texture(data->north);
	data->north = NULL;
	data->south_img = mlx_texture_to_image(data->mlx, data->south);
	mlx_delete_texture(data->south);
	data->south = NULL;
	data->east_img = mlx_texture_to_image(data->mlx, data->east);
	mlx_delete_texture(data->east);
	data->east = NULL;
	data->west_img = mlx_texture_to_image(data->mlx, data->west);
	mlx_delete_texture(data->west);
	data->west = NULL;
	data->door_img = mlx_texture_to_image(data->mlx, data->door_texture);
	mlx_delete_texture(data->door_texture);
	data->door_texture = NULL;
	if (!data->north_img || !data->south_img || !data->east_img
		|| !data->west_img || !data->door_img)
	{
		ft_putstr_fd("Error\nFailed to convert textures to images\n", 2);
		cleanup_map_info(data);
		exit(1);
	}
}

void	load_textures(t_map_info *data)
{
	load_texture_files(data);
	convert_textures_to_images(data);
}

static void	init_game(t_map_info *map)
{
	map->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D_bonus", true);
	if (!map->mlx)
	{
		cleanup_map_info(map);
		exit(1);
	}
	init_gun(map);
	init_sound_system(map);
	init_crosshair(map);
	map->color_effect_enabled = 0;
	mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
	load_textures(map);
	map->imgg = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->imgg)
	{
		print_error("Something happened", map);
		cleanup_map_info(map);
		exit(1);
	}
	mlx_image_to_window(map->mlx, map->imgg, 0, 0);
}

int	main(int ac, char **av)
{
	t_map_info	*map;

	map = parser(ac, av);
	if (!map)
	{
		ft_putstr_fd("Error\nFailed to parse arguments\n", 2);
		return (1);
	}
	mz_init_player(map);
	init_game(map);
	map->time = mlx_get_time();
	mlx_loop_hook(map->mlx, (void *)mz_draw, map);
	mlx_loop_hook(map->mlx, (void *)mz_key, map);
	mlx_loop(map->mlx);
	cleanup_gun(map);
	cleanup_sound_system(map);
	cleanup_crosshair(map);
	cleanup_map_info(map);
	free(map);
	return (0);
}
