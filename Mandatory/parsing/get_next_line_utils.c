/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:13:38 by sfellahi          #+#    #+#             */
/*   Updated: 2025/01/31 10:06:05 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*c1;
	ssize_t	i;
	ssize_t	r;

	i = -1;
	r = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	c1 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!c1)
		return (free(s1), s1 = NULL, NULL);
	while (s1[++i])
		c1[i] = s1[i];
	while (s2[r])
		c1[i++] = s2[r++];
	c1[i] = '\0';
	free(s1);
	return (c1);
}

char	*ft_ryhme(char *s)
{
	ssize_t	i;
	char	*ryhme;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	ryhme = malloc(i + 1);
	if (!ryhme)
		return (NULL);
	ryhme[i--] = '\0';
	while (i >= 0)
	{
		ryhme[i] = s[i];
		i--;
	}
	return (ryhme);
}

char	*next_ryhme(char *str)
{
	size_t	i;
	size_t	j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	s = malloc(ft_strlen(str) - i + 1);
	if (!s)
		return (NULL);
	i++;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}
