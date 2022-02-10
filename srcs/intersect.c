/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:11:37 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:11:41 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"

float	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_3d_vector	line_to_center;
	float		dot;
	float		d2;
	float		r2;
	float		thc;

	line_to_center = substract_vector(ray.origin, sphere.coordinates);
	dot = dot_product(line_to_center, ray.direction);
	d2 = dot_product(line_to_center, line_to_center) - (dot * dot);
	r2 = (sphere.diameter / 2) * (sphere.diameter / 2);
	if (d2 > r2)
		return (-1);
	thc = sqrtf(r2 - d2);
	return (smallest_above_zero(dot - thc, dot + thc));
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-
// ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
float	intersect_plane(t_ray ray, t_plane plane)
{
	float		otherside;
	float		dp;
	t_3d_vector	p;
	float		distance;

	otherside = 1;
	dp = dot_product(ray.direction, plane.orientation);
	if (dp < 0)
	{
		otherside = -1;
		dp *= -1;
	}
	if (dp < 0.00001)
		return (-1);
	p = substract_vector(ray.origin, plane.coordinates);
	distance = dot_product(p, plane.orientation);
	return (distance / dp * otherside);
}
