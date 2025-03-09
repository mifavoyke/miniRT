/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:06:56 by yhusieva          #+#    #+#             */
/*   Updated: 2023/08/18 17:06:57 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*to;
	unsigned const char	*from;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	to = (unsigned char *)dest;
	from = (unsigned const char *)src;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (dest);
}
