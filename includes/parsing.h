#ifndef PARSING_H
# define PARSING_H

#include "miniRT.h"
#include <fcntl.h>

t_scene parse_file(int fd);

int is_float(char *str);
int is_uint(char *str);

int parse_color(char *str, t_color *color);
int parse_coordinates(char *str, t_3d_vector *coordinates);
int parse_orientation(char *str, t_3d_vector *orientation);
int parse_brightness(char *str, float *brightness);

int	parse_cylinder(char **words, t_scene *scene);
int	parse_plane(char **words, t_scene *scene);
int	parse_sphere(char **words, t_scene *scene);

#endif
