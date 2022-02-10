/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
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

int	parse_line(char *line, t_scene *scene)
{
	char	**strs;
	int		return_value;

	if (!ft_strlen(line))
		return (1);
	return_value = -1;
	strs = ft_splits(line, " \t");
	if (!strs[0])
		return (-1);
	if (ft_strequal(strs[0], "A"))
		return_value = parse_ambient(strs, scene);
	if (ft_strequal(strs[0], "C"))
		return_value = parse_camera(strs, scene);
	if (ft_strequal(strs[0], "L"))
		return_value = parse_light(strs, scene);
	if (ft_strequal(strs[0], "sp"))
		return_value = parse_sphere(strs, scene);
	if (ft_strequal(strs[0], "pl"))
		return_value = parse_plane(strs, scene);
	if (ft_strequal(strs[0], "cy"))
		return_value = parse_cylinder(strs, scene);
	free_array(strs);
	return (return_value);
}

t_scene	parse_file(int fd)
{
	t_scene	scene;
	char	*line;
	int		continue_reading;

	scene.spheres = NULL;
	scene.spheres_count = 0;
	scene.planes = NULL;
	scene.planes_count = 0;
	scene.cylinders = NULL;
	scene.cylinder_count = 0;
	line = NULL;
	continue_reading = 1;
	while (continue_reading)
	{
		continue_reading = get_next_line(fd, &line);
		if (continue_reading == -1)
			malloc_error();
		if (parse_line(line, &scene) == -1)
		{
			free(line);
			parsing_error();
		}
		free(line);
	}
	return (scene);
}
