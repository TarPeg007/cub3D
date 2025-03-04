/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:51:21 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/17 09:30:27 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
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
