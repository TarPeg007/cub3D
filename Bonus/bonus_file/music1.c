/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:32:16 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/12 10:32:46 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_sound_system(t_map_info *map)
{
	if (!map)
		return ;
	map->sound = malloc(sizeof(t_sound));
	if (!map->sound)
		print_error("Error: Failed to allocate sound system\n", map);
	ft_memset(map->sound, 0, sizeof(t_sound));
	check_sound_files(map);
	if (pthread_mutex_init(&map->sound->thread.mutex, NULL) != 0)
	{
		free(map->sound);
		print_error("Error: Failed to initialize mutex\n", map);
	}
	map->sound->thread.should_exit = false;
	if (pthread_create(&map->sound->thread.id_sound, NULL,
			sound_effects_routine, map) != 0)
	{
		pthread_mutex_destroy(&map->sound->thread.mutex);
		free(map->sound);
		print_error("Error: Failed to create sound effects thread\n", map);
	}
}

void	cleanup_sound_system(t_map_info *map)
{
	if (!map || !map->sound)
		return ;
	pthread_mutex_lock(&map->sound->thread.mutex);
	map->sound->thread.should_exit = true;
	pthread_mutex_unlock(&map->sound->thread.mutex);
	pthread_join(map->sound->thread.id_sound, NULL);
	system("pkill afplay");
	pthread_mutex_destroy(&map->sound->thread.mutex);
	free(map->sound);
	map->sound = NULL;
}
