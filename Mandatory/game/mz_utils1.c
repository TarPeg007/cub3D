/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:00:55 by mzouine           #+#    #+#             */
/*   Updated: 2025/02/02 09:26:00 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

/*

FOV_ANGLE = POV * (PI / 180)
NUM_RAYS = width of the screen

rayAngle += FOV_ANGLE / NUM_RAYS
*/

float	mz_deg2rad(float degrees)
{
	return (degrees * (M_PI / 180));
}

float	mz_rad2deg(float radians)
{
	return (radians * (180 / M_PI));
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
