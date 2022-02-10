/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_calculations.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:14:24 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:14:27 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

float	dot_product(t_3d_vector v1, t_3d_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_3d_vector	cross_product(t_3d_vector v1, t_3d_vector v2)
{
	return (new_vector(
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x))
	);
}

t_3d_vector	substract_vector(t_3d_vector v1, t_3d_vector v2)
{
	t_3d_vector	substracted;

	substracted.x = v1.x - v2.x;
	substracted.y = v1.y - v2.y;
	substracted.z = v1.z - v2.z;
	return (substracted);
}

t_3d_vector	add_vector(t_3d_vector v1, t_3d_vector v2)
{
	t_3d_vector	added;

	added.x = v1.x + v2.x;
	added.y = v1.y + v2.y;
	added.z = v1.z + v2.z;
	return (added);
}

t_3d_vector	multiply_vector(t_3d_vector v, float factor)
{
	v.x *= factor;
	v.y *= factor;
	v.z *= factor;
	return (v);
}
