/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:24:04 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/12 18:21:59 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// make a function to get the 4x4 translation matrix
// t_coord translation_matrix[][]()
// {

// }

// MATH:
/* 
	// I is identity matrix = special matrix where all the diagonal elements are 1, and all the off-diagonal elements are 0 --> performs no transformation
	// I =  [  1  0  0 ]
	// 		[  0  1  0 ]
	// 		[  0  0  1 ]
	float identity_matrix[3][3];
	identity_matrix[0][0] = 1.0;
	identity_matrix[0][1] = 0.0;
	identity_matrix[0][2] = 0.0;
	identity_matrix[1][0] = 0.0;
	identity_matrix[1][1] = 1.0;
	identity_matrix[1][2] = 0.0;
	identity_matrix[2][0] = 0.0;
	identity_matrix[2][1] = 0.0;
	identity_matrix[2][2] = 1.0;
	
	skew-symmetric matrix K is a special matrix used in Rodrigues' rotation formula. 
	It represents the cross product operation in matrix form, allowing us to compute rotations efficiently.
	For any unit rotation axis vector 𝑘 = (𝑘𝑥,𝑘𝑦,𝑘𝑧), the skew-symmetric matrix Mk is:
	Mk = [  0  -kz  ky ] --> for our case where k(0, 0, -1) Mk = [   0   -(-1)  0 ]
		    [  kz  0  -kx ] 										[  -1     0    0 ]
		    [ -ky  kx   0 ]											[   0     0    0 ]
	float skew_matrix[3][3]; // sin(θ)K
	skew_matrix[0][0] = 0.0;
	skew_matrix[0][1] = sin(theta);
	skew_matrix[0][2] = 0.0;
	skew_matrix[1][0] = -sin(theta);
	skew_matrix[1][1] = 0.0;
	skew_matrix[1][2] = 0.0;
	skew_matrix[2][0] = 0.0;
	skew_matrix[2][1] = 0.0;
	skew_matrix[2][2] = 0.0;
	// Rotation Matrix R is then constructed.
	float k_squared[3][3]; // (1−cos(θ))K^2
	k_squared[0][0] = -(1 - cos(theta));
	k_squared[0][1] = 0.0;
	k_squared[0][2] = 0.0;
	k_squared[1][0] = 0.0;
	k_squared[1][1] = -(1 - cos(theta));
	k_squared[1][2] = 0.0;
	k_squared[2][0] = 0.0;
	k_squared[2][1] = 0.0;
	k_squared[2][2] = 0.0;
	
  --------------------------
	applying the camera-to-world to transform P from camera space to world space
	the matrix:
	T = R(rotation) * Tr(translation) = [[ Rx Ry Rz Tx ]
											[ Fx Fy Fz Ty ]
											[ Ux Uy Uz Tz ]
											[  0  0  0  1 ]]

	t_coord forward;	// vector along y axis
	t_coord right;		// vector along x axis
	t_coord up;			// vector along z axis
	t_coord global_up;	// temporary global vector (0, 0, 1) used for calculating

	global_up = set_coord(0.0, 0.0, 1.0);
	forward = v0; //c.vector; // F = vnew = camera.vector --> normalized
	right = get_cross_product(forward, global_up);
	normalize(&right);
	up = get_cross_product(right, forward);
	normalize(&up);

	so we have to apply the matrix to the point t get the transformed world coordinates
	Pnew.x = right.x * P0.x + right.y * P0.y + right.z * P0.z + translation.x;
	Pnew.y = forward.x * P0.x + forward.y * P0.y + forward.z * P0.z + translation.y;
	Pnew.z = up.x * P0.x + up.y * P0.y + up.z * P0.z + translation.z;
	
	*/
// TODO: MUST CHECK FOR CORRECTNESS AND IF THE MATRIX IS OK BUT I THINK IT LOOKS GOOD
// ALREADY MAPS ALL PIXELS DESCRIBED BY x AND y FROM SCREEN SPACE TO CAMERA SPACE TO 3D SPACE! <3
// maps coordinate from top-left 2d screen to the viewport plane in 3d
// in screen, one pixel is one unit defined by x and y, but they specify start of the pixel
// the middle of it is [x + 0.5, y + 0.5]
t_coord get_viewport_ray(t_camera c, t_viewport *v, int x, int y)
{
	// data needed to find transformation matrix
	t_coord P0; // this is variable for each ray
	t_coord Pnew;
	t_coord C0; // initial camera point for simplicity, C.new = camera.viewpoint
	t_coord v0; // initial camera vector for simplicity, vnew = camera.vector
	// vectors needed for the 4x4 translation matrix
	t_coord translation; // translation vector: Cnew - C0
	// used in Rodriguezes formula
	t_coord k;
	float theta;
	// final vector 
	t_coord ray_vector; // resulting vector
	
	// P0 are world coordinates of point but when camera is in the default position: C[0, 0, 0], ->v(0, 0, 1)
	P0.x = scale(x + 0.5, - v->viewport_width / 2, v->viewport_width / 2, WIDTH);
	P0.y = v->d;
	P0.z = scale(y + 0.5, v->viewport_height / 2, - v->viewport_height / 2, HEIGHT);
	
	// initial simple position and direction of camera
	C0 = set_coord(0.0, 0.0, 0.0);
	v0 = set_coord(0.0, 1.0, 0.0);

	// Rodrigues' rotation formula: R=I+sin(θ)K+(1−cos(θ))K^2
	// rodriguezes formula - !!! You cannot use Rodrigues' formula if both the original vector v0 and transformed vector vn are the same
	// if v0 is colinear with vn, change it 
	if (are_collinear(v0, c.vector))
		v0 = set_coord(0.0, 0.0, 1.0);
	// rotation angle θ is computed as θ=cos^(-1) (v0 . vn)
	theta = acos(get_dot_product(v0, c.vector)) * 180 / M_PI;
	// Rotation axis k is found as: k = 𝑣0 x vn
	k = get_cross_product(v0, c.vector);
	normalize(&k);
	
	translation.x = c.viewpoint.x; // - C0.x;
	translation.y = c.viewpoint.y; // - C0.y;
	translation.z = c.viewpoint.z; // - C0.z;
	// R=I+sin(θ)K+(1−cos(θ))K^2
	float Tm[4][4];
	Tm[0][0] = cos(theta);
	Tm[0][1] = sin(theta);
	Tm[0][2] = 0.0;
	Tm[0][3] = translation.x;
	Tm[1][0] = -sin(theta);
	Tm[1][1] = cos(theta);
	Tm[1][2] = 0.0;
	Tm[1][3] = translation.y;
	Tm[2][0] = 0.0;
	Tm[2][1] = 0.0;
	Tm[2][2] = 1.0;
	Tm[2][3] = translation.z;
	Tm[3][0] = 0.0;
	Tm[3][1] = 0.0;
	Tm[3][2] = 0.0;
	Tm[3][3] = 1.0;
	
	Pnew.x = Tm[0][0] * P0.x + Tm[0][1] * P0.y + Tm[0][2] * P0.z + Tm[0][3];
	Pnew.y = Tm[1][0] * P0.x + Tm[1][1] * P0.y + Tm[1][2] * P0.z + Tm[1][3];
	Pnew.z = Tm[2][0] * P0.x + Tm[2][1] * P0.y + Tm[2][2] * P0.z + Tm[2][3];
	// then we can apply the transformation matrix by adding Tx Ty Tz to last collumn adn 0 to last row, with 2 being the last element 
	ray_vector = make_vector(c.viewpoint, Pnew);
	if (x == 0 && y == 0)
	{
		printf("[%f\t%f\t%f\t%f\t]\n[%f\t%f\t%f\t%f\t]\n[%f\t%f\t%f\t%f\t]\n[%f\t%f\t%f\t%f\t]\n", Tm[0][0], Tm[0][1], Tm[0][2], Tm[0][3], Tm[1][0], Tm[1][1], Tm[1][2], Tm[1][3], Tm[2][0], Tm[2][1], Tm[2][2], Tm[2][3], Tm[3][0], Tm[3][1], Tm[3][2], Tm[3][3]);
		printf("P0 [%f, %f, %f] theta %f\nPnew [%f, %f, %f]\n -> final point vector v (%f, %f, %f)\n", P0.x, P0.y, P0.z, theta, Pnew.x, Pnew.y, Pnew.z, ray_vector.x, ray_vector.y, ray_vector.z);
		// printf("P0 [%f, %f, %f]\nF (%f, %f, %f)\nR (%f, %f, %f)\nU (%f, %f, %f)\nT (%f, %f, %f)\nPnew [%f, %f, %f]\n -> final point vector v (%f, %f, %f)\n", P0.x, P0.y, P0.z, forward.x, forward.y, forward.z, right.x, right.y, right.z, up.x, up.y, up.z, translation.x, translation.y, translation.z, Pnew.x, Pnew.y, Pnew.z, ray_vector.x, ray_vector.y, ray_vector.z);
	}
	return (ray_vector);
}

int shoot_rays(t_scene *scene)
{
	int     x;
	int     y;

	//t_coord viewport_point;
	//t_coord ray;
	// t_coord intersection;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			get_viewport_ray(scene->c, scene->viewport, x, y); // get coordinate on viewport as now we can make ray(vector) from camera through it to the scene
			//intersection = sphere_intersection(&viewport_point, &scene->c, scene->sp);
		}

	}
	return (0);
}
