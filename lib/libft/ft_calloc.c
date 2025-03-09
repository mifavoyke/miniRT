/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:28:23 by yhusieva          #+#    #+#             */
/*   Updated: 2023/08/23 16:28:25 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = num * size;
	if (num == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (total_size / num != size)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
