/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:05:53 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/20 17:42:43 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints error message nd returns 1
int	ft_error(const char *msg)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
}
