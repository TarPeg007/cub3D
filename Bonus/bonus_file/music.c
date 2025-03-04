/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:13:05 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/24 10:09:35 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static void	safe_system_play(const char *sound_path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		execl("/usr/bin/afplay", "afplay", sound_path, NULL);
		exit(1);
	}
	waitpid(pid, &status, 0);
}

void	check_sound_files(t_map_info *map)
{
	const char	*paths[3];
	int			i;

	paths[0] = RELOAD_SOUND_PATH;
	paths[1] = SHOOT_SOUND_PATH;
	i = 0;
	while (i < 2)
	{
		if (access(paths[i], F_OK | R_OK) == -1)
			print_error("Error: Cannot load sound files\n", map);
		i++;
	}
}

static void	handle_sound_effects(t_map_info *map, int *action)
{
	(void)map;
	if (*action == 1)
		safe_system_play(SHOOT_SOUND_PATH);
	else if (*action == 2)
		safe_system_play(RELOAD_SOUND_PATH);
}

static int	check_sound_action(t_map_info *map)
{
	int	action;

	action = 0;
	if (map->sound->play_shoot)
	{
		action = 1;
		map->sound->play_shoot = 0;
	}
	else if (map->sound->play_reload)
	{
		action = 2;
		map->sound->play_reload = 0;
	}
	return (action);
}

void	*sound_effects_routine(void *arg)
{
	t_map_info	*map;
	bool		should_exit;
	int			action;

	map = (t_map_info *)arg;
	while (1)
	{
		pthread_mutex_lock(&map->sound->thread.mutex);
		should_exit = map->sound->thread.should_exit;
		action = check_sound_action(map);
		pthread_mutex_unlock(&map->sound->thread.mutex);
		if (should_exit)
			break ;
		if (action)
			handle_sound_effects(map, &action);
		usleep(10000);
	}
	return (NULL);
}
