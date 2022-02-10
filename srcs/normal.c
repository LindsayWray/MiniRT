/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:12:22 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:12:25 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"

// Normal is the imaginary line pointing directly away 
//from an object from a point on the surface

t_3d_vector	sphere_normal(
	t_sphere sphere, t_3d_vector hitpoint, t_3d_vector camera_coordinates)
{
	t_3d_vector	normal;

	normal = normalize_vector(substract_vector(hitpoint, sphere.coordinates));
	if (inside_sphere(sphere, camera_coordinates))
		normal = multiply_vector(normal, -1);
	return (normal);
}

t_3d_vector	cylinder_normal(
	t_cylinder cy, t_3d_vector hitpoint, t_3d_vector camera_coordinates)
{
	t_3d_vector	top;
	t_3d_vector	bottom;
	t_3d_vector	normal;

	top = add_vector(cy.coordinates,
			multiply_vector(cy.orientation, cy.height * 0.5));
	bottom = substract_vector(cy.coordinates,
			multiply_vector(cy.orientation, cy.height * 0.5));
	normal = normalize_vector(cross_product(
				cy.orientation,
				cross_product(
					substract_vector(top, hitpoint),
					substract_vector(bottom, hitpoint)
					)
				));
	if (inside_cylinder(cy, camera_coordinates))
		normal = multiply_vector(normal, -1);
	return (normal);
}

// we know it should hit
// so first try one side, and if that one does not match
// (dp == 0 means that it DOES hit)
// the hit must be on the opposite side of the cylinder
t_3d_vector	cylinder_side_normal(
	t_cylinder cy, t_3d_vector hitpoint, t_3d_vector camera_coordinates)
{
	t_plane	side;
	float	dp;

	side.coordinates = substract_vector(cy.coordinates,
			multiply_vector(cy.orientation, cy.height / 2));
	side.orientation = multiply_vector(cy.orientation, -1);
	dp = dot_product(normalize_vector(
				substract_vector(hitpoint, side.coordinates)), cy.orientation);
	if (dp < -0.001 || dp > 0.001)
	{
		side.coordinates = add_vector(cy.coordinates,
				multiply_vector(cy.orientation, cy.height / 2));
		side.orientation = cy.orientation;
	}
	if (inside_cylinder(cy, camera_coordinates))
		side.orientation = multiply_vector(side.orientation, -1);
	return (side.orientation);
}
