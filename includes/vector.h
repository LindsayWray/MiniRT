/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 09:15:22 by lwray         #+#    #+#                 */
/*   Updated: 2022/02/10 09:15:25 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "miniRT.h"

t_3d_vector	new_vector(float x, float y, float z);

float		vector_length(t_3d_vector vec);
t_3d_vector	substract_vector(t_3d_vector point, t_3d_vector origin);
t_3d_vector	add_vector(t_3d_vector v1, t_3d_vector v2);
t_3d_vector	normalize_vector(t_3d_vector vec);
float		dot_product(t_3d_vector v1, t_3d_vector v2);
t_3d_vector	cross_product(t_3d_vector v1, t_3d_vector v2);
t_3d_vector	multiply_vector(t_3d_vector v, float factor);
t_3d_vector	rotate_vector(t_3d_vector v, t_matrix matrix);

#endif
