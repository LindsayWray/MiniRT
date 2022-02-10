/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:15:15 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:15:17 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "miniRT.h"
# include "cleanup.h"
# include <fcntl.h>

t_scene	parse_file(int fd);

int		parse_color(char *str, t_color *color);
int		parse_coordinates(char *str, t_3d_vector *coordinates);
int		parse_orientation(char *str, t_3d_vector *orientation);
int		parse_brightness(char *str, float *brightness);
int		parse_diameter(char *str, float *diameter);

int		string_array_len(char **strs);

int		parse_cylinder(char **words, t_scene *scene);
int		parse_plane(char **words, t_scene *scene);
int		parse_sphere(char **words, t_scene *scene);

#endif
