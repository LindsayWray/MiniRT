/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:13:12 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:13:15 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	parse_ambient(char	**strs, t_scene *scene)
{
	t_ambient	ambient;

	scene->ambient_count++;
	if (string_array_len(strs) != 3)
		return (-1);
	if (parse_brightness(strs[1], &ambient.brightness) == -1)
		return (-1);
	if (parse_color(strs[2], &(ambient.color)) == -1)
		return (-1);
	scene->ambient = ambient;
	return (0);
}

int	parse_camera(char	**strs, t_scene *scene)
{
	t_camera	camera;

	scene->camera_count++;
	if (string_array_len(strs) != 4)
		return (-1);
	if (parse_coordinates(strs[1], &(camera.coordinates)) == -1)
		return (-1);
	if (parse_orientation(strs[2], &(camera.orientation)) == -1)
		return (-1);
	if (!ft_is_uint(strs[3]))
		return (-1);
	camera.field_of_view = ft_atoi(strs[3]);
	if (camera.field_of_view > 180)
		return (-1);
	scene->camera = camera;
	return (0);
}

int	parse_light(char **strs, t_scene *scene)
{
	t_light	light;

	scene->light_count++;
	if (string_array_len(strs) != 4)
		return (-1);
	if (parse_coordinates(strs[1], &(light.coordinates)) == -1)
		return (-1);
	if (parse_brightness(strs[2], &light.brightness) == -1)
		return (-1);
	if (parse_color(strs[3], &(light.color)) == -1)
		return (-1);
	scene->light = light;
	return (0);
}
