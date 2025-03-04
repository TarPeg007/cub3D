/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:13:03 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/10 14:05:31 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*ft_read(int fd, char *str)
{
	int		bytes;
	char	*buff;

	bytes = 1;
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			(free(buff), buff = NULL, free(str), str = NULL);
			return (NULL);
		}
		buff[bytes] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	buff = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*store;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	store = ft_ryhme(str);
	str = next_ryhme(str);
	return (store);
}
