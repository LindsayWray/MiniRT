/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:14:05 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:14:08 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_3d_vector	new_vector(float x, float y, float z)
{
	t_3d_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float	vector_length(t_3d_vector vec)
{
	float	len;

	len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (len);
}

t_3d_vector	normalize_vector(t_3d_vector vec)
{
	float	length;

	length = vector_length(vec);
	vec.x /= length;
	vec.y /= length;
	vec.z /= length;
	return (vec);
}

t_3d_vector	rotate_vector(t_3d_vector v, t_matrix matrix)
{
	t_3d_vector	rot;

	rot.x = v.x * matrix.right.x + v.y * matrix.up.x + v.z * matrix.forward.x;
	rot.y = v.x * matrix.right.y + v.y * matrix.up.y + v.z * matrix.forward.y;
	rot.z = v.x * matrix.right.z + v.y * matrix.up.z + v.z * matrix.forward.z;
	return (rot);
}
