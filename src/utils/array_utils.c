/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:03 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/26 17:02:51 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints string array elements seprated by ( - )
void	print_arr(char **arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" - ");
		i++;
	}
	printf("\n");
}
