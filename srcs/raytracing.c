#include "../includes/miniRT.h"
#include "../includes/vector.h"
#include "../includes/color.h"

void	correction_camera_position(t_scene *scene) {
	int i;

	i = 0;
	while(i < scene->spheres_count) {
		scene->spheres[i].coordinates = substract_vector(scene->spheres[i].coordinates, scene->camera.coordinates);
		i++;
	}
	scene->camera.coordinates.x = 0;
	scene->camera.coordinates.y = 0;
	scene->camera.coordinates.z = 0;

}


t_ray	calculate_ray(int x, int y, int window_size, t_camera camera) {
	t_ray ray;
	// float theta = (float)camera.field_of_view * PI / 180.0;
	// float halfHeight = tan(theta / 2.0);


// float imageAspectRatio = imageWidth / (float)imageHeight; // assuming width > height 
// float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio; 
// float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180); 
// Vec3f rayOrigin(0); 
// Vec3f rayDirection = Vec3f(Px, Py, -1) - rayOrigin; // note that this just equal to Vec3f(Px, Py, -1); 
// rayDirection = normalize(rayDirection); // it's a direction so don't forget to normalize 

	t_3d_vector p;
	t_matrix matrix;

	p.x = (2 * ((x + 0.5) / window_size) - 1) * tan(camera.field_of_view / 2 * M_PI / 180); 
	p.y = (1 - 2 * ((y + 0.5) / window_size)) * tan(camera.field_of_view / 2 * M_PI / 180); 
	p.z = -1;
	ray.origin = camera.coordinates;

	matrix.forward = camera.orientation;
	matrix.right = cross_product(new_vector(0, 1, 0), matrix.forward);
	matrix.up = cross_product(matrix.forward, matrix.right);

	// ray.direction = normalize_vector(rotate_vector(substract_vector(p, ray.origin), matrix)); 
	// ray.direction = normalize_vector(substract_vector(p, ray.origin)); 
	t_3d_vector dir = normalize_vector(p);
	t_3d_vector rot = normalize_vector(rotate_vector(p, matrix)); 
	// printf("Direction %f,%f,%f; rotated=%f,%f,%f\n", dir.x, dir.y, dir.z, rot.x, rot.y, rot.z);
	ray.direction = rot;
	(void)dir;
	return (ray);	
}

t_color calculate_light_color(t_light light, t_ray ray, float d, t_sphere sphere) {
	t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, d));

	(void)hitpoint;

	// calculate shade

	// calculate light with angle
	t_3d_vector normal = normalize_vector(substract_vector(hitpoint, sphere.coordinates)); 
	t_3d_vector light_direction = normalize_vector(substract_vector(light.coordinates, hitpoint)); 
	float light_factor = dot_product(normal, light_direction) * light.brightness;
	if (light_factor < 0)
		light_factor = 0;
	light_factor /= 4 * M_PI * pow(vector_length(substract_vector(light.coordinates, hitpoint)), 2);

	return light.color;
}

t_color calculate_sphere_light(t_scene scene, t_ray ray, float d, t_sphere sphere) {
	t_color color;

	t_color ambient = new_color(
		(float)scene.ambient.color.r * scene.ambient.brightness,
		(float)scene.ambient.color.g * scene.ambient.brightness,
		(float)scene.ambient.color.b * scene.ambient.brightness
	);
	//printf("Ambient %d, %d, %d\n", ambient.r, ambient.g, ambient.b);
	color = mix_color(sphere.color, ambient);
	t_color light_color = calculate_light_color(scene.light, ray, d, sphere);
	color = add_colors(color, light_color);
	
	return color;
}

t_color calculate_pixel_color(t_ray ray, t_scene scene) {
	t_color c;
	float distance;
	float d;

	distance = -1; 
	c.r = c.g = c.b = 0; // start with a black pixel
	int i = 0;
	while(i < scene.spheres_count) {
		d = intersect_sphere(ray, scene.spheres[i]);
		if (d > 0 && (distance == -1 || d < distance))
		{
			distance = d;
			c = calculate_sphere_light(scene, ray, d, scene.spheres[i]);
		}
		i++;
	}

	return (c);
}