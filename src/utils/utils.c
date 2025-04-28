/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:05:53 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/04/26 17:28:34 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints error message nd returns 1
int	ft_error(const char *msg)
{
	printf("Error: %s\n", msg);
	return (ERROR);
}
