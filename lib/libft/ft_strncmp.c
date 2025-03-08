/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:08:22 by yhusieva          #+#    #+#             */
/*   Updated: 2023/06/25 15:08:24 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	s1;
	unsigned char	s2;

	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		s1 = (unsigned char)str1[i];
		s2 = (unsigned char)str2[i];
		if (s1 > s2)
		{
			return (1);
		}
		else if (s1 < s2)
		{
			return (-1);
		}
		else
		{
			i++;
		}
	}
	return (0);
}
