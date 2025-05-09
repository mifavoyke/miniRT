/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:52:46 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/09 10:52:47 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// prints possible key controls 
void	print_controls(void)
{
	printf("=== MINI-RT CONTROLS ===\n");
	printf("Close Program:\n");
	printf("  [ESC]             → Exit the program\n");
	printf("Camera Position:\n");
	printf("  [W] / [S]         → Move camera up/down (Z-axis)\n");
	printf("  [A] / [D]         → Move camera left/right (X-axis)\n");
	printf("  Scroll            → Zoom in/out (Y-axis forward/back)\n");
	printf("Camera Rotation:\n");
	printf("  [UP] / [DOWN]     → Pitch (rotate around X-axis - up/down)\n");
	printf("  [J] / [K]         → Roll (rotate Y-axis - tilt to sides)\n");
	printf("  [LEFT] / [RIGHT]  → Yaw (rotate around Z-axis-left/right)\n");
	printf("========================\n");
}
