/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:05:53 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/20 16:35:54 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints error message nd returns 1
int	ft_error(const char *msg)
{
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	return (ERROR);
}
