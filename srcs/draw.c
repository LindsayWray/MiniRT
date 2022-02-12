/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:10:33 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:10:37 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/parsing.h"
#include "../includes/cleanup.h"

int	key_hook(int key, t_minirt *minirt)
{
	if (key == ESC_KEY)
		close_window(minirt);
	return (0);
}

// helper function to get the color struct in the correct format
// and saved in the right place in memory within the MLX image
void	put_pixel_in_mlx_image(t_data *data, int x, int y, t_color color)
{
	char	*dst;
	int		color_int;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color_int = (color.r << 16) + (color.g << 8) + color.b;
	*(unsigned int *)dst = color_int;
}

void	init_mlx(t_minirt *minirt, t_scene scene, int size)
{
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
		mlx_error(scene);
	minirt->mlx_win = mlx_new_window(minirt->mlx, size, size, "miniRT");
	if (!minirt->mlx_win)
		mlx_error(scene);
	minirt->img.img = mlx_new_image(minirt->mlx, size, size);
	if (!minirt->img.img)
	{
		mlx_destroy_window(minirt->mlx, minirt->mlx_win);
		mlx_error(scene);
	}
	minirt->img.addr = mlx_get_data_addr(minirt->img.img,
			&minirt->img.bits_per_pixel,
			&minirt->img.line_length, &minirt->img.endian);
	minirt->scene = scene;
}

// x and y to loop over all pixels in our MLX window
// ray is imaginary line starting at the camera coordinates and with direction
// pixel_color: the calculated color that the specific pixel should have
// mlx_init() will establish a connection to the correct graphical system and 
//  will return a void * which holds the location of our current MLX instance.
// mlx_new_window() will create a popup window
// mlx_new_image() will create an MLX image, on that can put our colored pixels
// mlx_get_data_addr() gets data from OS and stores it in a struct

// mlx_put_image_to_window() will send the whole image in one time to the 
//  mlx window, this is much faster than sending each pixel separate to window
// mlx_hook 17  => close on clicking red X
// mlx_key_hook =>  to make sure ESC also stops program
// mlx_loop to keep window open
//  */
void	draw_window(t_scene scene, int size)
{
	t_minirt	minirt;
	int			x;
	int			y;
	t_ray		ray;
	t_color		pixel_color;

	init_mlx(&minirt, scene, size);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			ray = calculate_ray(x, size - y - 1, size, scene.camera);
			pixel_color = calculate_pixel_color(ray, scene);
			put_pixel_in_mlx_image(&minirt.img, x, y, pixel_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt.mlx, minirt.mlx_win, minirt.img.img, 0, 0);
	mlx_hook(minirt.mlx_win, 17, 1L << 17, close_window, &minirt);
	mlx_key_hook(minirt.mlx_win, key_hook, &minirt);
	mlx_loop(minirt.mlx);
}
