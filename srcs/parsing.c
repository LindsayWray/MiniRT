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

int	parse_line(char *line, t_scene *scene)
{
	char	**strs;
	int		return_value;

	if (!ft_strlen(line))
		return (0);
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

void	empty_scene(t_scene *scene)
{
	scene->camera_count = 0;
	scene->ambient_count = 0;
	scene->light_count = 0;
	scene->spheres = NULL;
	scene->spheres_count = 0;
	scene->planes = NULL;
	scene->planes_count = 0;
	scene->cylinders = NULL;
	scene->cylinder_count = 0;
}

t_scene	parse_file(int fd)
{
	t_scene	scene;
	char	*line;
	int		continue_reading;

	empty_scene(&scene);
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
			parsing_error(scene);
		}
		free(line);
	}
	if (scene.camera_count != 1 || scene.ambient_count != 1
		|| scene.light_count != 1)
		parsing_error(scene);
	return (scene);
}
