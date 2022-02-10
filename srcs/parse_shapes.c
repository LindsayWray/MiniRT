/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_shapes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:12:56 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:12:59 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	string_array_len(char **strs)
{
	int	count;

	count = 0;
	while (*strs)
	{
		count++;
		strs++;
	}
	return (count);
}

int	parse_sphere(char **strs, t_scene *scene)
{
	t_sphere	sphere;
	t_sphere	*old_pointer;

	if (string_array_len(strs) != 4)
		return (-1);
	scene->spheres_count++;
	if (parse_coordinates(strs[1], &(sphere.coordinates)) == -1)
		return (-1);
	if (parse_diameter(strs[2], &sphere.diameter) == -1)
		return (-1);
	if (parse_color(strs[3], &(sphere.color)) == -1)
		return (-1);
	old_pointer = scene->spheres;
	scene->spheres = malloc(scene->spheres_count * sizeof(t_sphere));
	if (!scene->spheres)
	{
		free(old_pointer);
		malloc_error();
	}
	if (old_pointer)
		ft_memcpy(scene->spheres, old_pointer,
			(scene->spheres_count - 1) * sizeof(t_sphere));
	scene->spheres[scene->spheres_count - 1] = sphere;
	free(old_pointer);
	return (0);
}

int	parse_plane(char **strs, t_scene *scene)
{
	t_plane	plane;
	t_plane	*old_pointer;

	if (string_array_len(strs) != 4)
		return (-1);
	scene->planes_count++;
	if (parse_coordinates(strs[1], &(plane.coordinates)) == -1)
		return (-1);
	if (parse_orientation(strs[2], &(plane.orientation)) == -1)
		return (-1);
	if (parse_color(strs[3], &(plane.color)) == -1)
		return (-1);
	old_pointer = scene->planes;
	scene->planes = malloc(scene->planes_count * sizeof(t_plane));
	if (!scene->planes)
	{
		free(old_pointer);
		malloc_error();
	}
	if (old_pointer)
		ft_memcpy(scene->planes, old_pointer,
			(scene->planes_count - 1) * sizeof(t_plane));
	scene->planes[scene->planes_count - 1] = plane;
	free(old_pointer);
	return (0);
}

void	add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_cylinder	*old_pointer;

	old_pointer = scene->cylinders;
	scene->cylinders = malloc(scene->cylinder_count * sizeof(t_cylinder));
	if (!scene->cylinders)
	{
		free(old_pointer);
		malloc_error();
	}
	if (old_pointer)
		ft_memcpy(scene->cylinders, old_pointer,
			(scene->cylinder_count - 1) * sizeof(t_cylinder));
	scene->cylinders[scene->cylinder_count - 1] = cylinder;
	free(old_pointer);
}

int	parse_cylinder(char **strs, t_scene *scene)
{
	t_cylinder	cylinder;

	if (string_array_len(strs) != 6)
		return (-1);
	if (parse_coordinates(strs[1], &(cylinder.coordinates)) == -1)
		return (-1);
	if (parse_orientation(strs[2], &(cylinder.orientation)) == -1)
		return (-1);
	if (parse_diameter(strs[3], &cylinder.diameter) == -1)
		return (-1);
	if (parse_diameter(strs[4], &cylinder.height) == -1)
		return (-1);
	if (parse_color(strs[5], &(cylinder.color)) == -1)
		return (-1);
	scene->cylinder_count++;
	add_cylinder(scene, cylinder);
	return (0);
}
