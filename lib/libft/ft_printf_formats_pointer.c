/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formats_pointer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:18:43 by yhusieva          #+#    #+#             */
/*   Updated: 2024/02/06 16:18:44 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptr_length(unsigned long long arr)
{
	int	length;

	length = 0;
	while (arr)
	{
		arr /= 16;
		length++;
	}
	return (length);
}

static void	ft_hex_ptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_hex_ptr(num / 16);
	}
	ft_char(ft_hex_base(num % 16));
}

int	ft_pointer(void *arr)
{
	unsigned long long	ull;
	int					count;

	count = 0;
	ull = (unsigned long long)arr;
	count = 0;
	if (ull == 0)
	{
		ft_string("(nil)");
		count += 5;
	}
	else
	{
		ft_string("0x");
		count += 2;
		ft_hex_ptr(ull);
		count += ft_ptr_length(ull);
	}
	return (count);
}
