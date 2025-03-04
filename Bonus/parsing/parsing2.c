/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:48:21 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/09 14:44:12 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	check_commas(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			comma_count++;
			if (str[i + 1] == ',')
				return (0);
		}
		i++;
	}
	return (comma_count == 2);
}

static int	validate_color_value(char *color)
{
	int	j;
	int	digit_found;

	j = 0;
	digit_found = 0;
	while (color[j] == ' ' || color[j] == '\t')
		j++;
	while (ft_isdigit(color[j]))
	{
		digit_found = 1;
		j++;
	}
	while (color[j] == ' ' || color[j] == '\t')
		j++;
	return (color[j] == '\0' && digit_found);
}

static int	validate_color_range(char **colors)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (colors[i] && i < 3)
	{
		if (!validate_color_value(colors[i]))
			return (0);
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (i == 3 && colors[3] == NULL);
}

int	is_valid_rgb(char *str)
{
	char	**colors;
	int		ret;

	if (!check_commas(str))
		return (0);
	colors = ft_split(str, ',');
	if (!colors)
		return (0);
	ret = validate_color_range(colors);
	ft_free_array(colors);
	return (ret);
}
