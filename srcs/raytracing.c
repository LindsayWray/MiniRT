#include "../includes/miniRT.h"
#include "../includes/vector.h"
#include "../includes/color.h"

void	correction_camera_position(t_scene *scene) { //not used!
	int i;

	i = 0;
	while(i < scene->spheres_count) {
		scene->spheres[i].coordinates = substract_vector(scene->spheres[i].coordinates, scene->camera.coordinates);
		i++;
	}
	scene->light.coordinates = substract_vector(scene->light.coordinates, scene->camera.coordinates);
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

	p.x = (2 * (((float)x + 0.5) / window_size) - 1) * tan(camera.field_of_view / 2 * M_PI / 180); 
	p.y = (1 - 2 * (((float)y + 0.5) / (float)window_size)) * tan(camera.field_of_view / 2 * M_PI / 180); 
	p.z = -1;
	ray.origin = camera.coordinates;

	// printf("DirectionN %f,%f,%f\n", p.x, p.y, p.z);


	matrix.forward = normalize_vector(camera.orientation);
	matrix.right = cross_product(new_vector(0, 1, 0), matrix.forward);
	matrix.up = cross_product(matrix.forward, matrix.right);

	// TRY this

	// //this works, but rotated
	// t_3d_vector vv = multiply_vector( new_vector(matrix.forward.y, matrix.forward.z, matrix.forward.x), 1);
	// matrix.right = cross_product(vv, matrix.forward);
	// // printf("VV %f,%f,%f\n", vv.x, vv.y, vv.z);
	// t_3d_vector vvv = multiply_vector( new_vector(-matrix.forward.z, matrix.forward.x, matrix.forward.y), 1);
	// matrix.up = cross_product(vvv, matrix.forward);
 	// // --------


	//this works, but rotated
	// matrix.right = multiply_vector( new_vector(matrix.forward.z, matrix.forward.y, matrix.forward.x), -1);
	// // printf("VV %f,%f,%f\n", vv.x, vv.y, vv.z);
	// // t_3d_vector vvv = multiply_vector( new_vector(-matrix.forward.z, matrix.forward.x, matrix.forward.y), 1);
	// matrix.up = cross_product(matrix.forward, matrix.right);
 	// --------
	if (camera.orientation.z == 0 && camera.orientation.x == 0)
	{
	matrix.right = multiply_vector( new_vector(matrix.forward.x, matrix.forward.z, matrix.forward.y), -1);
	// printf("VV %f,%f,%f\n", vv.x, vv.y, vv.z);
	// t_3d_vector vvv = multiply_vector( new_vector(-matrix.forward.z, matrix.forward.x, matrix.forward.y), 1);
	matrix.up = multiply_vector( new_vector(matrix.forward.y, matrix.forward.x, matrix.forward.z), -1);
	}

 	// --------


	// printf("Matrix %f,%f,%f \n%f,%f,%f\n%f,%f,%f\n", 
	// matrix.forward.x, matrix.forward.y, matrix.forward.z, 
	// matrix.right.x, matrix.right.y, matrix.right.z,
	// matrix.up.x, matrix.up.y, matrix.up.z);


	// ray.direction = normalize_vector(rotate_vector(substract_vector(p, ray.origin), matrix)); 
	// ray.direction = normalize_vector(substract_vector(p, ray.origin)); 
	// t_3d_vector dir = normalize_vector(p);
	t_3d_vector rot = normalize_vector(rotate_vector(p, matrix)); 
	// printf("Direction %f,%f,%f; rotated=%f,%f,%f\n", dir.x, dir.y, dir.z, rot.x, rot.y, rot.z);
	ray.direction = rot;


	// correct for topview from here


	// printf("Direction %f,%f,%f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	// printf("Ray origin %f,%f,%f\n", ray.origin.x, ray.origin.y, ray.origin.z);

	// (void)dir;
	return (ray);	
}

float has_shade(t_3d_vector hitpoint, t_3d_vector light_direction, t_scene scene) {
	float distance = -1;
	float d;
	t_ray towards_light;

	towards_light.origin = hitpoint;
	towards_light.direction = multiply_vector(light_direction, -1);

	int i = 0;
	while(i < scene.spheres_count) 
	{
		d = intersect_sphere(towards_light, scene.spheres[i]);
		if (d > 0.01 && (distance == -1 || d < distance))  // small difference to make sure a point is not shaded by itself due to rounding
			distance = d;
		i++;
	}
	i = 0;
	while(i < scene.planes_count) {
		d = intersect_plane(towards_light, scene.planes[i]);
		if (d > 0.01 && (distance == -1 || d < distance))
			distance = d;
		i++;
	}
	i = 0;
	while(i < scene.cylinder_count) {
		d = intersect_cy(towards_light, scene.cylinders[i]);
		if (d > 0.01 && (distance == -1 || d < distance))
			distance = d;
		d = intersect_cylinder_side(towards_light, scene.cylinders[i]);
		if (d > 0.01 && (distance == -1 || d < distance))
			distance = d;
		i++;
	}
	return (distance);
}

int inside_sphere(t_sphere sphere, t_3d_vector coordinates) {
	if (vector_length(substract_vector(coordinates, sphere.coordinates)) < (sphere.diameter / 2))
		return 1;
	return 0;
}

int inside_cylinder(t_cylinder cy, t_3d_vector coordinates) {

	t_3d_vector top = add_vector(cy.coordinates, multiply_vector(cy.orientation, cy.height * 0.5));
	t_3d_vector bottom = substract_vector(cy.coordinates, multiply_vector(cy.orientation, cy.height * 0.5));

	t_3d_vector top_to_bottom = substract_vector(top, bottom);

	float dp = dot_product(top_to_bottom, substract_vector(coordinates, bottom));
	if (dp < 0 || dp > cy.height)
		return 0; // on the line top to bottom, further than top or lower than bottom

	t_3d_vector place_in_pipe = substract_vector(top, add_vector(bottom, multiply_vector(cy.orientation, dp)));
	// printf("Between top and bottom %f,%f,%f ", place_in_pipe.x, place_in_pipe.y, place_in_pipe.z);
	// printf("Coordinates %f,%f,%f\n", coordinates.x, coordinates.y, coordinates.z);
	// printf("Distance %f\n", vector_length(substract_vector(coordinates, place_in_pipe)));

	if (vector_length(substract_vector(coordinates, place_in_pipe)) > (cy.diameter / 2))
		return 0; // larger than radius away from center	
	return 1;
}

t_color calculate_sphere_light_color(t_light light, t_ray ray, float d, t_sphere sphere, t_scene scene) {
	t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * d));
	

	t_3d_vector light_direction = normalize_vector(substract_vector(light.coordinates, hitpoint)); 
	float len = vector_length(substract_vector(light.coordinates, hitpoint));

	// calculate shade
	float obstruction = has_shade(hitpoint, light_direction, scene);
	if (obstruction > 0 && obstruction < len)
	{
		return new_color(0,0,0);
	}


	// calculate light with angle
	t_3d_vector normal = normalize_vector(substract_vector(hitpoint, sphere.coordinates)); 
	if (inside_sphere(sphere, scene.camera.coordinates))
		normal = multiply_vector(normal, -1);
	float light_factor = dot_product(normal, light_direction) * light.brightness;

	if (light_factor < 0)
		light_factor = 0;
	t_color cc = new_color(
		light.color.r * light_factor,
		light.color.g * light_factor,
		light.color.b * light_factor
	);
	return mix_color(cc, sphere.color);
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
	t_color light_color = calculate_sphere_light_color(scene.light, ray, d, sphere, scene);
	color = add_colors(color, light_color);
	
	return color;
}

t_color calculate_plane_light_color(t_light light, t_ray ray, float d, t_plane plane, t_scene scene) {
	t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * d));
	
	t_3d_vector light_direction = normalize_vector(substract_vector(light.coordinates, hitpoint)); 
	float len = vector_length(substract_vector(light.coordinates, hitpoint));

	// calculate shade
	float obstruction = has_shade(hitpoint, light_direction, scene);
	if (obstruction > 0 && obstruction < len)
		return new_color(0,0,0);

	// calculate light with angle
	t_3d_vector normal = plane.orientation; 
	float light_factor = dot_product(normal, light_direction) * light.brightness;

	if (light_factor < 0)
		light_factor = 0;
	t_color cc = new_color(
		light.color.r * light_factor,
		light.color.g * light_factor,
		light.color.b * light_factor
	);
	return mix_color(cc, plane.color);
}

t_color calculate_plane_light(t_scene scene, t_ray ray, float d, t_plane plane) {
	t_color color;

	t_color ambient = new_color(
		(float)scene.ambient.color.r * scene.ambient.brightness,
		(float)scene.ambient.color.g * scene.ambient.brightness,
		(float)scene.ambient.color.b * scene.ambient.brightness
	);
	//printf("Ambient %d, %d, %d\n", ambient.r, ambient.g, ambient.b);
	color = mix_color(plane.color, ambient);
	t_color light_color = calculate_plane_light_color(scene.light, ray, d, plane, scene);
	color = add_colors(color, light_color);

	(void)ray;
	(void)d;
	
	return color;
}

t_color calculate_cylinder_light_color(t_light light, t_ray ray, float d, t_cylinder cy, t_scene scene) {
	t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * d));
	
	t_3d_vector light_direction = normalize_vector(substract_vector(light.coordinates, hitpoint)); 
	float len = vector_length(substract_vector(light.coordinates, hitpoint));

	// calculate shade
	float obstruction = has_shade(hitpoint, light_direction, scene);
	if (obstruction > 0 && obstruction < len)
		return new_color(0,0,0);

	// calculate light with angle
	t_3d_vector top = add_vector(cy.coordinates, multiply_vector(cy.orientation, cy.height * 0.5));
	t_3d_vector bottom = substract_vector(cy.coordinates, multiply_vector(cy.orientation, cy.height * 0.5));

	t_3d_vector normal = normalize_vector(cross_product(
		cy.orientation,
		cross_product(
			substract_vector(top, hitpoint),
			substract_vector(bottom, hitpoint)
		)
	));

	if (inside_cylinder(cy, scene.camera.coordinates))
		normal = multiply_vector(normal, -1);

	float light_factor = dot_product(normal, light_direction) * light.brightness;

	if (light_factor < 0)
		light_factor = 0;
	t_color cc = new_color(
		light.color.r * light_factor,
		light.color.g * light_factor,
		light.color.b * light_factor
	);
	return mix_color(cc, cy.color);
}

t_color calculate_cylinder_light(t_scene scene, t_ray ray, float d, t_cylinder cy) {
	t_color color;

	t_color ambient = new_color(
		(float)scene.ambient.color.r * scene.ambient.brightness,
		(float)scene.ambient.color.g * scene.ambient.brightness,
		(float)scene.ambient.color.b * scene.ambient.brightness
	);
	//printf("Ambient %d, %d, %d\n", ambient.r, ambient.g, ambient.b);
	color = mix_color(cy.color, ambient);
	t_color light_color = calculate_cylinder_light_color(scene.light, ray, d, cy, scene);
	color = add_colors(color, light_color);

	return color;
}

t_color calculate_cylinder_side_light(t_scene scene, t_ray ray, float d, t_cylinder cy) {
	t_plane side;

	side.coordinates = substract_vector(cy.coordinates, multiply_vector(cy.orientation, cy.height / 2)); // try out one side
	side.orientation = multiply_vector(cy.orientation, -1);

	side.color = cy.color;

	t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * d));
	float dp = dot_product(normalize_vector(substract_vector(hitpoint, side.coordinates)), cy.orientation);

	if (dp < -0.001 || dp > 0.001) // chose the wrong side, so switching to other end of cylinder
	{
		side.coordinates = add_vector(cy.coordinates, multiply_vector(cy.orientation, cy.height / 2));
		side.orientation = cy.orientation;
	}
	if (inside_cylinder(cy, scene.camera.coordinates))
	{
		// printf("Watching plane from inside cylinder\n");
		side.orientation = multiply_vector(side.orientation, -1);
	}
	return calculate_plane_light(scene, ray, d, side);
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
	i = 0;
	while(i < scene.planes_count) {
		d = intersect_plane(ray, scene.planes[i]);
		if (d > 0 && (distance == -1 || d < distance))
		{
			distance = d;
			c = calculate_plane_light(scene, ray, d, scene.planes[i]);
		}
		i++;
	}
	i = 0;
	while(i < scene.cylinder_count) {
		d = intersect_cy(ray, scene.cylinders[i]);
		if (d > 0 && (distance == -1 || d < distance))
		{
			distance = d;
			c = calculate_cylinder_light(scene, ray, d, scene.cylinders[i]);
		}
		d = intersect_cylinder_side(ray, scene.cylinders[i]);
		if (d > 0 && (distance == -1 || d < distance))
		{
			distance = d;
			c = calculate_cylinder_side_light(scene, ray, d, scene.cylinders[i]);
		}
		i++;
	}
	return (c);
}