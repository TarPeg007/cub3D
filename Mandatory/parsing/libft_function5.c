/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:05:23 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/15 13:02:29 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

void	set_error(t_map_info *info, char *message)
{
	info->has_error = 1;
	info->error_message = message;
}

void	print_error(char *msg, t_map_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	if (info)
	{
		cleanup_map_info(info);
		free(info);
	}
	exit(1);
}
