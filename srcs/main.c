#include "../includes/miniRT.h"
#include "../includes/parsing.h"



int	close_window(t_minirt *minirt)
{
	//free_scene(scene); TODO 
	//free_images(); TODO
	mlx_destroy_window(minirt->mlx, minirt->mlx_win);
	system("leaks miniRT");
	printf("coming through here\n");
	exit(EXIT_SUCCESS);
}

int	key_hook(int key, t_minirt *minirt)
{
	if (key == 53)
		close_window(minirt);
	return (0);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;
	int		color_int;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color_int = (color.r << 16) + (color.g << 8) + color.b;

	*(unsigned int*)dst = color_int;
}

int	main(int argc, char **argv)
{
	t_minirt minirt;
	int 	fd;
	t_scene scene;
	int		window_size = 700;

	if (argc != 2 || !ends_with(argv[1], ".rt")) 
		file_error("Please provide a correct filename\n");
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		perror("Could not open scene file");
	}
	scene = parse_file(fd);
	close(fd);
	//correction_camera_position(&scene);
	// printf("AMBIENT: brightness: %f, Color %d,%d,%d\n", 
	// 	scene.ambient.brightness,
	// 	scene.ambient.color.r, scene.ambient.color.g,scene.ambient.color.b);
	// printf("CAMERA: angle: %d, coordinates %f,%f,%f, orientation %f,%f,%f\n", 
	// 	scene.camera.field_of_view, 
	// 	scene.camera.coordinates.x, scene.camera.coordinates.y, scene.camera.coordinates.z, 
	// 	scene.camera.orientation.x, scene.camera.orientation.y, scene.camera.orientation.z);
	// printf("LIGHT: coordinates %f,%f,%f, brightness: %f, Color %d,%d,%d\n", 
	// 	scene.light.coordinates.x, scene.light.coordinates.y, scene.light.coordinates.z, 
	// 	scene.light.brightness,
	// 	scene.light.color.r, scene.light.color.g, scene.light.color.b);
	// printf("SPHERES: coordinates %f,%f,%f, coordinates %f,%f,%f\n", 
	// 	scene.spheres[0].coordinates.x, scene.spheres[0].coordinates.y, scene.spheres[0].coordinates.z, 
	// 	scene.spheres[1].coordinates.x, scene.spheres[1].coordinates.y, scene.spheres[1].coordinates.z);
	// printf("PLANES: Color %d,%d,%d, Color %d,%d,%d\n", 
	// 	scene.planes[0].color.r, scene.planes[0].color.g, scene.planes[0].color.b, 
	// 	scene.planes[1].color.r, scene.planes[1].color.g, scene.planes[1].color.b);
	// printf("CYLINDERS: %d, Color %d,%d,%d, Color %d,%d,%d\n", 
	// 	scene.cylinder_count,
	// 	scene.cylinders[0].color.r, scene.cylinders[0].color.g, scene.cylinders[0].color.b, 
	// 	scene.cylinders[1].color.r, scene.cylinders[1].color.g, scene.cylinders[1].color.b);
	minirt.mlx = mlx_init(); //This will establish a connection to the correct graphical system and will return a void * which holds the location of our current MLX instance.
	minirt.mlx_win = mlx_new_window(minirt.mlx, window_size, window_size, "miniRT");
	minirt.img.img = mlx_new_image(minirt.mlx, window_size, window_size);

	minirt.img.addr = mlx_get_data_addr(minirt.img.img, &minirt.img.bits_per_pixel, &minirt.img.line_length, &minirt.img.endian);

	// t_ray left_top = calculate_ray(0, 0, window_size, scene.camera);
	// printf("Left top ray: origin %f,%f,%f; direction: %f,%f,%f\n",
	// 	left_top.origin.x, left_top.origin.y, left_top.origin.z,
	// 	left_top.direction.x, left_top.direction.y, left_top.direction.z
	// );
	// t_ray right_bottom = calculate_ray(window_size, window_size, window_size, scene.camera);
	// printf("Right bottom ray: origin %f,%f,%f; direction: %f,%f,%f\n",
	// 	right_bottom.origin.x, right_bottom.origin.y, right_bottom.origin.z,
	// 	right_bottom.direction.x, right_bottom.direction.y, right_bottom.direction.z
	// );
	// t_ray middle = calculate_ray(400, 400, window_size, scene.camera);
	// printf("Middle ray: origin %f,%f,%f; direction: %f,%f,%f\n",
	// 	middle.origin.x, middle.origin.y, middle.origin.z,
	// 	middle.direction.x, middle.direction.y, middle.direction.z
	// );

	int x = 0;
	int y = 0;
	t_color pixel_color;
	t_ray ray;
	while(y < window_size) 
	{
		x = 0;
		while (x < window_size)
		{
			//printf("X: %d, Y: %d\n", x, y);
			ray = calculate_ray(x, window_size - y - 1, window_size, scene.camera);
			pixel_color = calculate_pixel_color(ray, scene);
			my_mlx_pixel_put(&minirt.img, x, y, pixel_color);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(minirt.mlx, minirt.mlx_win, minirt.img.img, 0, 0);
	mlx_hook(minirt.mlx_win, 17, 1L << 17, close_window, &minirt);
	mlx_key_hook(minirt.mlx_win, key_hook, &minirt);

	mlx_loop(minirt.mlx);

	system("leaks miniRT");
}

