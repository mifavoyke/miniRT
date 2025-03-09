/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:55:28 by yhusieva          #+#    #+#             */
/*   Updated: 2024/02/01 16:55:30 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_counter(size_t n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_printnum(int n)
{
	char	c;

	c = n + '0';
	write(1, &c, 1);
}

int	ft_number(int n)
{
	int	i;

	i = 0;
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		i += ft_char('-');
		n = -n;
	}
	i += char_counter(n);
	if (n < 10)
		ft_printnum(n);
	else
	{
		ft_number(n / 10);
		ft_printnum(n % 10);
	}
	return (i);
}

int	ft_unsigned_dec(unsigned int num)
{
	char	c;
	int		i;

	i = 0;
	if (num < 10)
	{
		c = num + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_unsigned_dec(num / 10);
		c = (num % 10) + '0';
		write(1, &c, 1);
	}
	i += char_counter(num);
	return (i);
}
