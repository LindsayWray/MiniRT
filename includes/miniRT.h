#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include <mlx.h>
# include "../libft/libft.h"
#include "error_handler.h"
#include "cleanup.h"


typedef struct s_3d_vector {
	float x;
	float y;
	float z;
} t_3d_vector;

typedef struct		s_matrix
{
	t_3d_vector			forward;
	t_3d_vector			right;
	t_3d_vector			up;
}					t_matrix;

typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

typedef struct s_ambient
{
	t_color		color;
	float		brightness;
} t_ambient;

typedef struct s_camera
{
	t_3d_vector	coordinates;
	t_3d_vector	orientation;
	int			field_of_view;
} t_camera;

typedef struct s_light
{
	t_3d_vector	coordinates;
	float 		brightness;
	t_color 	color;
} t_light;

typedef struct s_sphere
{
	t_3d_vector	coordinates;
	float		diameter;
	t_color		color;
} t_sphere;

typedef struct s_plane
{
	t_3d_vector	coordinates;
	t_3d_vector	orientation;
	t_color		color;
} t_plane;

typedef struct s_cylinder
{
	t_3d_vector	coordinates;
	t_3d_vector	orientation;
	float		diameter;
	float		height;
	t_color		color;
} t_cylinder;

typedef struct s_scene {
	t_ambient 	ambient;
	t_camera 	camera;
	t_light 	light;
	t_sphere	*spheres;
	int			spheres_count;
	t_plane		*planes;
	int			planes_count;
	t_cylinder	*cylinders;
	int			cylinder_count;
} t_scene;

typedef struct s_ray {
	t_3d_vector	origin;
	t_3d_vector	direction;
} t_ray;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_minirt {
	t_scene	scene;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
}				t_minirt;

void	correction_camera_position(t_scene *scene);
t_ray	calculate_ray(int x, int y, int window_size, t_camera camera);
t_color calculate_pixel_color(t_ray ray, t_scene scene);

float	intersect_sphere(t_ray ray, t_sphere sphere);

#endif