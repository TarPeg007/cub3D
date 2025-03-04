/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:10:02 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/10 16:53:01 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bb;
	unsigned char	cc;
	size_t			i;

	bb = (unsigned char *) b;
	cc = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		bb[i] = cc;
		i++;
	}
	return (b);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1) + 1;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len);
	return (dup);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	source = (unsigned char *)src;
	destination = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}
