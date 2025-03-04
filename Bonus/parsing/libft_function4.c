/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_function4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfellahi <sfellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:50 by sfellahi          #+#    #+#             */
/*   Updated: 2025/02/10 16:53:48 by sfellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*sad;
	size_t			le;

	sad = (unsigned char *) s;
	le = 0;
	while (le < n)
	{
		sad[le] = 0;
		le++;
	}
}
