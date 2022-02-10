/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inside_objects.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:11:16 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:11:21 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/vector.h"

int	inside_sphere(t_sphere sphere, t_3d_vector coordinates)
{
	float	distance_from_center;

	distance_from_center = vector_length(
			substract_vector(coordinates, sphere.coordinates));
	if (distance_from_center < (sphere.diameter / 2))
		return (1);
	return (0);
}

// 
// dp is too check whether the point is between the op and bottom
// < 0 ; below bottom, > cy.height: above top
//
// place_in_pipe is the point on the imaginary line from top 
// to bottom that corresponds with the given coordinates
// 
// lastly, check if the coordinates are further 
// away than radius from the place_in_pipe
int	inside_cylinder(t_cylinder cy, t_3d_vector coordinates)
{
	t_3d_vector	top;
	t_3d_vector	bottom;
	t_3d_vector	top_to_bottom;
	float		dp;
	t_3d_vector	place_in_pipe;

	top = add_vector(
			cy.coordinates,
			multiply_vector(cy.orientation, cy.height * 0.5));
	bottom = substract_vector(
			cy.coordinates,
			multiply_vector(cy.orientation, cy.height * 0.5));
	top_to_bottom = substract_vector(top, bottom);
	dp = dot_product(top_to_bottom, substract_vector(coordinates, bottom));
	if (dp < 0 || dp > cy.height)
		return (0);
	place_in_pipe = substract_vector(
			top,
			add_vector(bottom, multiply_vector(cy.orientation, dp)));
	if (vector_length(substract_vector(coordinates, place_in_pipe))
		> (cy.diameter / 2))
		return (0);
	return (1);
}
