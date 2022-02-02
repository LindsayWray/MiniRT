#include "../includes/parsing.h"

int is_uint(char *str) { // naar libft
	int i;

	if (!str || !ft_strlen(str))
		return (0);

	i = 0;
	while(i < ft_strlen(str)) {
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int is_float(char *str) { // naar libft
	int i;

	if (!str || !ft_strlen(str))
		return (0);

	i = 0;
	if (str[i] == '-')
		i++;
	while(i < ft_strlen(str)) {
		if (!ft_isdigit(str[i]))
			break;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	if (str[i] == '.') {
		i++;
		return (is_uint(str + i));
	}
	return (0);
}

int parse_color(char *str, t_color *color) {
	char		**rgb;
	int i;

	if (!str)
		return (-1);

	rgb = ft_split(str, ',');
	i = 0;
	while(i < 3) //check for too many color!
	{
		if (!rgb[i] || !is_uint(rgb[i]))
			return free_array(rgb);
		i++;
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
		return (-1);
	return (0);
}

int parse_coordinates(char *str, t_3d_vector *coordinates) {
	char		**xyz;
	int i;

	if (!str)
		return (-1);
	xyz = ft_split(str, ',');
	i = 0;
	while(i < 3) //check for too many coordinates!
	{
		if (!xyz[i] || !is_float(xyz[i]))
			return (free_array(xyz));
		i++;
	}
	coordinates->x = ft_atof(xyz[0]);
	coordinates->y = ft_atof(xyz[1]);
	coordinates->z = ft_atof(xyz[2]);
	free_array(xyz);
	return (0);
}

int parse_orientation(char *str, t_3d_vector *orientation) {
	char		**xyz;
	int i;

	if (!str)
		return (-1);
	xyz = ft_split(str, ',');
	i = 0;
	while(i < 3)
	{
		if (!xyz[i] || !is_float(xyz[i]))
			return free_array(xyz);
		i++;
	}
	orientation->x = ft_atof(xyz[0]);
	orientation->y = ft_atof(xyz[1]);
	orientation->z = ft_atof(xyz[2]);
	free_array(xyz);
	if (orientation->x < -1 || orientation->x > 1 || orientation->y < -1 || orientation->y > 1 || orientation->z < -1 || orientation->z > 1)
		return (-1);
	return (0);
}

int parse_brightness(char *str, float *brightness) {
	if (!is_float(str))		
		return (-1);
	*brightness = ft_atof(str);
	if (*brightness < 0 || *brightness > 1)
		return (-1);
	return (0);
}

int parse_diameter(char *str, float *diameter) {
	if (!is_float(str))		
		return (-1);
	*diameter = ft_atof(str);
	if (*diameter < 0)
		return (-1);
	return (0);
}

int	parse_sphere(char **strs, t_scene *scene) {
	t_sphere sphere;
	t_sphere *old_pointer;

	scene->spheres_count++;
	if (parse_coordinates(strs[1], &(sphere.coordinates)) == -1)
		return free_array(strs);
	if (parse_diameter(strs[2], &sphere.diameter) == -1)
		return free_array(strs);
	if (parse_color(strs[3], &(sphere.color)) == -1)
		return free_array(strs);
	free_array(strs);

	old_pointer = scene->spheres;
	scene->spheres = malloc(scene->spheres_count * sizeof(t_sphere));
	if (!scene->spheres)
	{
		free(old_pointer);
		malloc_error();
	}
	if (old_pointer)
		ft_memcpy(scene->spheres, old_pointer, (scene->spheres_count - 1) * sizeof(t_sphere));
	scene->spheres[scene->spheres_count - 1] = sphere;
	free(old_pointer);
	return (0);
}

int	parse_plane(char **strs, t_scene *scene) {
	t_plane plane;
	t_plane *old_pointer;

	scene->planes_count++;
	if (parse_coordinates(strs[1], &(plane.coordinates)) == -1)
		return free_array(strs);
	if (parse_orientation(strs[2], &(plane.orientation)) == -1)
		return free_array(strs);
	if (parse_color(strs[3], &(plane.color)) == -1)
		return free_array(strs);
	free_array(strs);

	old_pointer = scene->planes;
	scene->planes = malloc(scene->planes_count * sizeof(t_plane));
	if (!scene->planes)
	{
		free(old_pointer);
		malloc_error();
	}
	if (old_pointer)
		ft_memcpy(scene->planes, old_pointer, (scene->planes_count - 1) * sizeof(t_plane));
	scene->planes[scene->planes_count - 1] = plane;
	free(old_pointer);
	return (0);
}

int	parse_cylinder(char **strs, t_scene *scene) {
	t_cylinder cylinder;
	t_cylinder *old_pointer;

	scene->cylinder_count++;
	if (parse_coordinates(strs[1], &(cylinder.coordinates)) == -1)
		return free_array(strs);
	if (parse_orientation(strs[2], &(cylinder.orientation)) == -1)
		return free_array(strs);
	if (parse_diameter(strs[3], &cylinder.diameter) == -1)
		return free_array(strs);
	if (parse_diameter(strs[4], &cylinder.height) == -1)
		return free_array(strs);
	if (parse_color(strs[5], &(cylinder.color)) == -1)
		return free_array(strs);
	free_array(strs);

	old_pointer = scene->cylinders;
	scene->cylinders = malloc(scene->cylinder_count * sizeof(t_cylinder));
	if (!scene->cylinders)
	{
		free(old_pointer);
		malloc_error();
	}
	if (old_pointer)
		ft_memcpy(scene->cylinders, old_pointer, (scene->cylinder_count - 1) * sizeof(t_cylinder));
	scene->cylinders[scene->cylinder_count - 1] = cylinder;
	free(old_pointer);
	return (0);
}