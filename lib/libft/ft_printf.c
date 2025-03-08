/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:55:18 by yhusieva          #+#    #+#             */
/*   Updated: 2024/02/01 16:55:20 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	arg;
	int		i;
	int		length;

	va_start(arg, fmt);
	i = 0;
	length = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			length += ft_conversions(fmt[i + 1], arg);
			i++;
		}
		else
			length += ft_char(fmt[i]);
		i++;
	}
	va_end(arg);
	return (length);
}
