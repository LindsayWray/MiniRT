#include "../includes/miniRT.h"
#include "../includes/vector.h"

float	intersect_sphere(t_ray ray, t_sphere sphere) {

	t_3d_vector line_to_center = substract_vector(ray.origin, sphere.coordinates);
	float dot = dot_product(line_to_center, ray.direction);
	float d2 = dot_product(line_to_center, line_to_center) - (dot * dot);
	float r2 = (sphere.diameter / 2) * (sphere.diameter / 2);

	if (d2 > r2)
		return -1; 
	float thc = sqrtf(r2 - d2); 
	float t0 = dot - thc; 
	float t1 = dot + thc; 
	if (t0 > 0 && (t0 < t1 || t1 < 0))
		return t0;
	if (t1 > 0 && (t1 < t0 || t0 < 0))
		return t1;
	return -1;
}

float	intersect_plane(t_ray ray, t_plane plane) {
	float otherside = 1;

	float dp = dot_product(ray.direction, plane.orientation);
	if (dp < 0)
	{
		otherside = -1;
		dp *= -1;
	}
	if (dp < 0.00001)
		return (-1);
	// if (dp > 1.0) 
	// 	printf("This is weird %f\n", dp);
	//  Vec3f p0l0 = p0 - l0; 
    // t = dotProduct(p0l0, n) / denom; 
    // return (t >= 0); 
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

	t_3d_vector p = substract_vector(ray.origin, plane.coordinates);
	float distance = dot_product(p, plane.orientation);
	return distance / dp * otherside;
}

float	intersect_cylinder_side(t_ray ray, t_cylinder cylinder) 
{
	float distance = -1;
	// top and bottom coordinates of cylinder
	t_3d_vector side_one = substract_vector(cylinder.coordinates, multiply_vector(cylinder.orientation, cylinder.height / 2));
	t_3d_vector side_two = add_vector(cylinder.coordinates, multiply_vector(cylinder.orientation, cylinder.height / 2));

	// see if it hits one side (as a plane with hitpoint closer to the side-centre than radius)
	t_plane cylinder_side;
	cylinder_side.orientation = multiply_vector(cylinder.orientation, -1);
	cylinder_side.coordinates = side_one;

	float distance_to_plane = intersect_plane(ray, cylinder_side);
	t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * distance_to_plane));
	if (vector_length(substract_vector(hitpoint, side_one)) < (cylinder.diameter / 2))
		distance = distance_to_plane;

	// same for other side
	cylinder_side.orientation = cylinder.orientation;
	cylinder_side.coordinates = side_two;
	distance_to_plane = intersect_plane(ray, cylinder_side);
	if (distance_to_plane > 0 && (distance < 0 || (distance_to_plane < distance)))
	{
		hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * distance_to_plane));
		if (vector_length(substract_vector(hitpoint, side_two)) < (cylinder.diameter / 2))
		{
			// printf("Hitting other side %f\n", distance_to_plane);
			distance = distance_to_plane;
		}
	}
	return (distance);	
}

float	intersect_cy(t_ray ray, t_cylinder cylinder) {
	// top and bottom coordinates of cylinder
	t_3d_vector side_one = substract_vector(cylinder.coordinates, multiply_vector(cylinder.orientation, cylinder.height / 2));
	t_3d_vector side_two = add_vector(cylinder.coordinates, multiply_vector(cylinder.orientation, cylinder.height / 2));

	t_3d_vector c0 = substract_vector(ray.direction, multiply_vector(cylinder.orientation, dot_product(ray.direction, cylinder.orientation)));
	t_3d_vector distance_ray_to_center_cy = substract_vector(ray.origin, cylinder.coordinates);
	t_3d_vector c1 = substract_vector(
		distance_ray_to_center_cy,
		multiply_vector(cylinder.orientation, dot_product(distance_ray_to_center_cy, cylinder.orientation)));

	// ABC formula to calculate if the ray hits the side
	float a = powf(vector_length(c0), 2);
	float b = 2.0 * dot_product(c0, c1);
	float c = powf(vector_length(c1), 2) - powf(cylinder.diameter / 2, 2); // - r^2
	float discriminant = powf(b, 2) - 4 * a * c;
	// printf("Discriminant %f, a = %f, b = %f, c = %f\n", discriminant, a , b, c);

	if (discriminant < 0) // no solution for ABC formula: no hit
		return (-1); 
	else if (discriminant < 0.0001) // D ~= 0 -> one hit
	{
		float t = ((-1 * b) / (2.0 * a));
		t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * t));

		// calculate if between the bot and bottom of cylinder
		if (dot_product(cylinder.orientation, substract_vector(hitpoint, side_one)) < 0)
			return (-1); 
		if (dot_product(cylinder.orientation, substract_vector(hitpoint, side_two)) > 0)
			return (-1); 
		return t;
	}
	else // two hits, need to calculate closest
	{ 
		float t;
		float x1 = ((b) + sqrt(discriminant)) / (2.0 * a);
		float x2 = ((b) - sqrt(discriminant)) / (2.0 * a);
		// printf("x1 %f, x2 %f\n", x1, x2);

		if (x1 > 0 && (x1 < x2 || x2 < 0))
			t = x1;
		else if (x2 > 0 && (x2 < x1 || x1 < 0))
			t = x2;
		else
			return (-1); 
		t_3d_vector hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * t));

		// calculate if between the bot and bottom of cylinder
		if (dot_product(cylinder.orientation, substract_vector(hitpoint, side_one)) < 0)
			return (-1);
		if (dot_product(cylinder.orientation, substract_vector(hitpoint, side_two)) > 0)
			return (-1);
		return t;

	}
	return (-1);
}
