/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_cylinder.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:11:57 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:12:00 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"

static void	check_side(t_plane cylinder_side,
	t_ray ray, float radius, float *distance)
{
	t_3d_vector	hitpoint;
	float		distance_to_plane;

	distance_to_plane = intersect_plane(ray, cylinder_side);
	hitpoint = add_vector(ray.origin,
			multiply_vector(ray.direction, -1 * distance_to_plane));
	if (vector_length(substract_vector(hitpoint, cylinder_side.coordinates))
		< radius)
	{
		*distance = smallest_above_zero(*distance, distance_to_plane);
	}
}

// side one and two are the flat sides of the cylinder
// for each side
//    treat side as a plane
//    if it hits, and the hitpoint is closer to 
//    the side middlepoint than the radius, it hits that side
// returns whichever side is closer to the ray origin
float	intersect_cylinder_side(t_ray ray, t_cylinder cylinder)
{
	float		distance;
	t_3d_vector	side_middle_point;
	t_plane		cylinder_side;

	distance = -1;
	side_middle_point = substract_vector(cylinder.coordinates,
			multiply_vector(cylinder.orientation, cylinder.height / 2));
	cylinder_side.orientation = multiply_vector(cylinder.orientation, -1);
	cylinder_side.coordinates = side_middle_point;
	check_side(cylinder_side, ray, cylinder.diameter / 2, &distance);
	side_middle_point = add_vector(cylinder.coordinates,
			multiply_vector(cylinder.orientation, cylinder.height / 2));
	cylinder_side.orientation = cylinder.orientation;
	cylinder_side.coordinates = side_middle_point;
	check_side(cylinder_side, ray, cylinder.diameter / 2, &distance);
	return (distance);
}

// ABC formula to calculate if the ray hits the side
// returns -1 if not hitting the cylinder
float	abc_formula(float a, float b, float c)
{
	float	discriminant;
	float	x1;
	float	x2;

	discriminant = powf(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	if (discriminant < 0.0001)
		return ((-1 * b) / (2.0 * a));
	x1 = ((b) + sqrt(discriminant)) / (2.0 * a);
	x2 = ((b) - sqrt(discriminant)) / (2.0 * a);
	return (smallest_above_zero(x1, x2));
}

// intersect ray with round side of cylinder
// first use ABC formula to check if the ray would hit the cylinder
// if it was infinitely long
// then check if the hitpoint is between the top and bottom of the cylinder
float	intersect_cy(t_ray ray, t_cylinder cy)
{
	t_3d_vector	c0;
	t_3d_vector	distance_ray_to_center_cy;
	t_3d_vector	c1;
	t_3d_vector	hitpoint;
	float		t;

	c0 = substract_vector(ray.direction, multiply_vector(cy.orientation,
				dot_product(ray.direction, cy.orientation)));
	distance_ray_to_center_cy = substract_vector(ray.origin, cy.coordinates);
	c1 = substract_vector(distance_ray_to_center_cy,
			multiply_vector(cy.orientation,
				dot_product(distance_ray_to_center_cy, cy.orientation)));
	t = abc_formula(powf(vector_length(c0), 2), 2.0 * dot_product(c0, c1),
			powf(vector_length(c1), 2) - powf(cy.diameter / 2, 2));
	if (t < 0)
		return (t);
	hitpoint = add_vector(ray.origin, multiply_vector(ray.direction, -1 * t));
	if (dot_product(cy.orientation, substract_vector(hitpoint,
				substract_vector(cy.coordinates,
					multiply_vector(cy.orientation, cy.height / 2)))) < 0
		|| dot_product(cy.orientation, substract_vector(hitpoint,
				add_vector(cy.coordinates,
					multiply_vector(cy.orientation, cy.height / 2)))) > 0)
		return (-1);
	return (t);
}
