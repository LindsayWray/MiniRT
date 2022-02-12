/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raytracing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:13:29 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:13:33 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"

// based on x and y in MLX image
// and camera properties (cooridnates, orientation and field of view)
// create a ray (imaginary line in 3D) 
// coming from the camera with a certain direction
// z==0 && x==0: fix for top-down view
t_ray	calculate_ray(int x, int y, int window_size, t_camera camera)
{
	t_ray		ray;
	t_3d_vector	p;
	t_matrix	matrix;
	float		angle;

	angle = tan(camera.field_of_view / 2 * M_PI / 180);
	p.x = (2 * (((float)x + 0.5) / window_size) - 1) * angle;
	p.y = (1 - 2 * (((float)y + 0.5) / (float)window_size)) * angle;
	p.z = -1;
	ray.origin = camera.coordinates;
	matrix.forward = normalize_vector(camera.orientation);
	matrix.right = cross_product(new_vector(0, 1, 0), matrix.forward);
	matrix.up = cross_product(matrix.forward, matrix.right);
	if (camera.orientation.z == 0 && camera.orientation.x == 0)
	{
		matrix.right = multiply_vector(new_vector(
					matrix.forward.x, matrix.forward.z, matrix.forward.y), -1);
		matrix.up = multiply_vector(new_vector(
					matrix.forward.y, matrix.forward.x, matrix.forward.z), -1);
	}
	ray.direction = normalize_vector(rotate_vector(p, matrix));
	return (ray);
}
