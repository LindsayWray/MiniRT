/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object_properties.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:12:39 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:12:43 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/vector.h"

int	parse_color(char *str, t_color *color)
{
	char	**rgb;
	int		i;

	if (!str)
		return (-1);
	rgb = ft_split(str, ',');
	if (string_array_len(rgb) != 3)
		return (free_array(rgb));
	i = 0;
	while (i < 3)
	{
		if (!rgb[i] || !ft_is_uint(rgb[i]))
			return (free_array(rgb));
		i++;
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_array(rgb);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (-1);
	return (0);
}

int	parse_coordinates(char *str, t_3d_vector *coordinates)
{
	char	**xyz;
	int		i;

	if (!str)
		return (-1);
	xyz = ft_split(str, ',');
	if (string_array_len(xyz) != 3)
		return (free_array(xyz));
	i = 0;
	while (i < 3)
	{
		if (!xyz[i] || !ft_is_float(xyz[i]))
			return (free_array(xyz));
		i++;
	}
	coordinates->x = ft_atof(xyz[0]);
	coordinates->y = ft_atof(xyz[1]);
	coordinates->z = ft_atof(xyz[2]);
	free_array(xyz);
	return (0);
}

int	parse_orientation(char *str, t_3d_vector *orientation)
{
	char	**xyz;
	int		i;

	if (!str)
		return (-1);
	xyz = ft_split(str, ',');
	i = 0;
	while (i < 3)
	{
		if (!xyz[i] || !ft_is_float(xyz[i]))
			return (free_array(xyz));
		i++;
	}
	orientation->x = ft_atof(xyz[0]);
	orientation->y = ft_atof(xyz[1]);
	orientation->z = ft_atof(xyz[2]);
	free_array(xyz);
	if (orientation->x < -1 || orientation->x > 1 || orientation->y < -1
		|| orientation->y > 1 || orientation->z < -1 || orientation->z > 1)
		return (-1);
	if (vector_length(*orientation) > 1.1 || vector_length(*orientation) < 0.9)
		return (-1);
	return (0);
}

int	parse_brightness(char *str, float *brightness)
{
	if (!ft_is_float(str))
		return (-1);
	*brightness = ft_atof(str);
	if (*brightness < 0 || *brightness > 1)
		return (-1);
	return (0);
}

int	parse_diameter(char *str, float *diameter)
{
	if (!ft_is_float(str))
		return (-1);
	*diameter = ft_atof(str);
	if (*diameter < 0)
		return (-1);
	return (0);
}
