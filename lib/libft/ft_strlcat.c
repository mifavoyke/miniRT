/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:44:43 by yhusieva          #+#    #+#             */
/*   Updated: 2025/03/08 14:42:57 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	total;

	i = 0;
	j = 0;
	if (dest == 0 && size == 0)
		return (ft_strlen((char *)src));
	while (dest[i] != '\0' && i < size)
		i++;
	while (src[j] != '\0')
		j++;
	total = i + j;
	j = 0;
	while (src[j] != '\0' && i + 1 < size)
		dest[i++] = src[j++];
	if (i < size)
		dest[i] = '\0';
	return (total);
}
