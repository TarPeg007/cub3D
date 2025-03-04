/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:10:55 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/13 19:05:21 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	ft_free_array(char **arr)
{
	int	n;

	n = 0;
	if (!arr)
		return ;
	while (arr[n])
	{
		free(arr[n]);
		n++;
	}
	free(arr);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	len_of_number(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len += 1;
	}
	while (n)
	{
		len += 1;
		n /= 10;
	}
	return (len);
}

static char	*fill(char *ptr, long long ln, int size)
{
	int	i;

	if (ln == 0)
	{
		ptr[0] = '0';
		ptr[1] = 0;
		return (ptr);
	}
	if (ln < 0)
	{
		ptr[0] = '-';
		ln *= -1;
	}
	i = size - 1;
	while (ln)
	{
		ptr[i] = '0' + ln % 10;
		ln /= 10;
		i--;
	}
	ptr[size] = 0;
	return (ptr);
}

char	*ft_itoa(int n)
{
	int			size;
	long long	ln;
	char		*ptr;

	ln = (long long)n;
	size = len_of_number(ln);
	ptr = malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	fill(ptr, ln, size);
	return (ptr);
}
