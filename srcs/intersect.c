#include "../includes/miniRT.h"
#include "../includes/vector.h"

float	intersect_sphere(t_ray ray, t_sphere sphere) {

	// float t0, t1; // solutions for t if the ray intersects 
	// // geometric solution
	// Vec3f L = center - orig; 
	// float tca = L.dotProduct(dir); 
	// // if (tca < 0) return false;
	// float d2 = L.dotProduct(L) - tca * tca; 
	// if (d2 > radius2) return false; 
	// float thc = sqrt(radius2 - d2); 
	// t0 = tca - thc; 
	// t1 = tca + thc; 

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


	// oc = v_minus(ray.origin, sp.center);
	// a = v_length_squared(ray.dir);
	// b = v_dot(oc, ray.dir);
	// c = v_length_squared(oc) - sp.radius * sp.radius;
	// d = b * b - a * c;
	// if (d < 0)
	// 	return (-1);
	// *t = (b * -1 - sqrt(d)) / a;
	// if (*t < scope.x || *t > scope.y)
	// {
	// 	*t = (b * -1 + sqrt(d)) / a;
	// 	if (*t < scope.x || *t > scope.y)
	// 		return (-1);
	// }
	// return (1);




}