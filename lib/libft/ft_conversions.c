/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:55:05 by yhusieva          #+#    #+#             */
/*   Updated: 2024/02/01 16:55:07 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conversions(const char type, va_list arg)
{
	int	length;

	length = 0;
	if (type == 'c')
		length += ft_char(va_arg(arg, int));
	else if (type == 's')
		length += ft_string(va_arg(arg, char *));
	else if (type == 'p')
		length += ft_pointer(va_arg(arg, void *));
	else if (type == 'd' || type == 'i')
		length += ft_number(va_arg(arg, int));
	else if (type == 'u')
		length += ft_unsigned_dec(va_arg(arg, unsigned int));
	else if (type == 'x' || type == 'X')
		length += ft_hexadecimal(va_arg(arg, unsigned int), type, 0);
	else if (type == '%')
		length += ft_percent();
	return (length);
}
