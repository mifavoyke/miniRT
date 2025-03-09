/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formats_xX.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:47:18 by yhusieva          #+#    #+#             */
/*   Updated: 2024/02/05 11:47:20 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_base(int num)
{
	int	c;

	if (num == 0)
		c = '0';
	else if (num < 10)
		c = num + '0';
	else if (num >= 10 && num <= 15)
		c = 'a' + (num - 10);
	else
		c = '\0';
	return (c);
}

int	ft_hexadecimal(unsigned int num, const char type, int count)
{
	int	c;
	int	remainder;

	if (num < 16)
	{
		c = ft_hex_base(num);
		if (type == 'X')
			c = ft_toupper(c);
		count += ft_char(c);
	}
	else
	{
		remainder = num % 16;
		count += ft_hexadecimal((num / 16), type, count);
		c = ft_hex_base(remainder);
		if (type == 'X')
			c = ft_toupper(c);
		count += ft_char(c);
	}
	return (count);
}
