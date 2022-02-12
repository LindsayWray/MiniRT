/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_pixel_color.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:09:58 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:10:01 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"
#include "../includes/color.h"

void	hit_spheres(t_ray ray, t_scene scene, t_object_hit *hit)
{
	int		i;
	float	d;

	i = 0;
	while (i < scene.spheres_count)
	{
		d = intersect_sphere(ray, scene.spheres[i]);
		if (d > 0 && (hit->distance == -1 || d < hit->distance))
		{
			hit->distance = d;
			hit->coordinates = add_vector(ray.origin,
					multiply_vector(ray.direction, -1 * d));
			hit->normal = sphere_normal(scene.spheres[i],
					hit->coordinates, scene.camera.coordinates);
			hit->object_color = scene.spheres[i].color;
		}
		i++;
	}
}

void	hit_planes(t_ray ray, t_scene scene, t_object_hit *hit)
{
	int		i;
	float	d;

	i = 0;
	while (i < scene.planes_count)
	{
		d = intersect_plane(ray, scene.planes[i]);
		if (d > 0 && (hit->distance == -1 || d < hit->distance))
		{
			hit->distance = d;
			hit->coordinates = add_vector(ray.origin,
					multiply_vector(ray.direction, -1 * d));
			hit->normal = plane_normal(scene.planes[i],
					hit->coordinates, scene.camera.coordinates);
			hit->object_color = scene.planes[i].color;
		}
		i++;
	}
}

void	hit_cylinders(t_ray ray, t_scene scene, t_object_hit *hit)
{
	int		i;
	float	d;

	i = 0;
	while (i < scene.cylinder_count)
	{
		d = intersect_cy(ray, scene.cylinders[i]);
		if (d > 0 && (hit->distance == -1 || d < hit->distance))
		{
			hit->distance = d;
			hit->coordinates = add_vector(ray.origin,
					multiply_vector(ray.direction, -1 * d));
			hit->normal = cylinder_normal(scene.cylinders[i],
					hit->coordinates, scene.camera.coordinates);
			hit->object_color = scene.cylinders[i].color;
		}
		i++;
	}
}

void	hit_cylinders_sides(t_ray ray, t_scene scene, t_object_hit *hit)
{
	int		i;
	float	d;

	i = 0;
	while (i < scene.cylinder_count)
	{
		d = intersect_cylinder_side(ray, scene.cylinders[i]);
		if (d > 0 && (hit->distance == -1 || d < hit->distance))
		{
			hit->distance = d;
			hit->coordinates = add_vector(ray.origin,
					multiply_vector(ray.direction, -1 * d));
			hit->normal = cylinder_side_normal(scene.cylinders[i],
					hit->coordinates, scene.camera.coordinates);
			hit->object_color = scene.cylinders[i].color;
		}
		i++;
	}
}

//hit distance < 0 ==>  no object hit, results in a black pixel
// hit is the closest object that is hit by the ray
t_color	calculate_pixel_color(t_ray ray, t_scene scene)
{
	t_color			ambient;
	t_object_hit	hit;

	ambient = color_factor(scene.ambient.color, scene.ambient.brightness);
	hit.distance = -1;
	hit_spheres(ray, scene, &hit);
	hit_planes(ray, scene, &hit);
	hit_cylinders(ray, scene, &hit);
	hit_cylinders_sides(ray, scene, &hit);
	if (hit.distance < 0)
		return (new_color(0, 0, 0));
	return (add_colors(
			mix_color(hit.object_color, ambient),
			calculate_light_color(hit, scene)
		));
}
