/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_light_color.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:09:30 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:09:35 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"
#include "../includes/color.h"

// 0.01 => small difference to make sure a point is
// not shaded by itself due to rounding
static void	check_dist(float *old_distance, float new_distance)
{
	if (new_distance > 0.001)
	{
		if (*old_distance == -1 || new_distance < *old_distance)
			*old_distance = new_distance;
	}
}

static float	has_shade(t_ray light_ray, t_scene scene)
{
	float	distance;
	int		i;

	distance = -1;
	i = 0;
	while (i < scene.spheres_count)
	{
		check_dist(&distance, intersect_sphere(light_ray, scene.spheres[i]));
		i++;
	}
	i = 0;
	while (i < scene.planes_count)
	{
		check_dist(&distance, intersect_plane(light_ray, scene.planes[i]));
		i++;
	}
	i = 0;
	while (i < scene.cylinder_count)
	{
		check_dist(&distance, intersect_cy(light_ray, scene.cylinders[i]));
		check_dist(&distance,
			intersect_cylinder_side(light_ray, scene.cylinders[i]));
		i++;
	}
	return (distance);
}

// ray going from light source to the hitpoint
t_ray	get_light_ray(t_3d_vector hitpoint, t_3d_vector light_direction)
{
	t_ray	light_ray;

	light_ray.origin = hitpoint;
	light_ray.direction = multiply_vector(light_direction, -1);
	return (light_ray);
}

// light_to_hit = vector going from light to the hit coordinates
t_color	calculate_light_color(t_object_hit hit, t_scene scene)
{
	t_3d_vector	light_direction;
	float		distance_to_light;
	float		obstruction;
	float		light_factor;
	t_3d_vector	light_to_hit;

	light_to_hit = substract_vector(scene.light.coordinates, hit.coordinates);
	light_direction = normalize_vector(light_to_hit);
	distance_to_light = vector_length(light_to_hit);
	obstruction = has_shade(get_light_ray(hit.coordinates, light_direction),
			scene);
	if (obstruction > 0 && obstruction < distance_to_light)
		return (new_color(0, 0, 0));
	light_factor = dot_product(hit.normal, light_direction)
		* scene.light.brightness;
	if (light_factor < 0)
		light_factor = 0;
	return (mix_color(color_factor(scene.light.color, light_factor),
			hit.object_color));
}
