#include "../includes/miniRT.h"

t_3d_vector new_vector(float x, float y, float z)
{
	t_3d_vector vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float vector_length(t_3d_vector vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_3d_vector normalize_vector(t_3d_vector vec)
{
	float length;

	length = vector_length(vec);

	vec.x /= length;
	vec.y /= length;
	vec.z /= length;
	return vec;
}

t_3d_vector substract_vector(t_3d_vector v1, t_3d_vector v2) 
{
	t_3d_vector substracted;

	substracted.x = v1.x - v2.x;
	substracted.y = v1.y - v2.y;
	substracted.z = v1.z - v2.z;
	return substracted;
}

t_3d_vector add_vector(t_3d_vector v1, t_3d_vector v2)
{
	t_3d_vector added;

	added.x = v1.x + v2.x;
	added.y = v1.y + v2.y;
	added.z = v1.z + v2.z;
	return added;
}

float dot_product(t_3d_vector v1, t_3d_vector v2)
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

t_3d_vector multiply_vector(t_3d_vector v, float factor)
{
	v.x *= factor;
	v.y *= factor;
	v.z *= factor;
	return (v);
}


t_3d_vector		rotate_vector(t_3d_vector v, t_matrix matrix)
{
	t_3d_vector rot;

	rot.x = v.x * matrix.right.x + v.y * matrix.up.x + v.z * matrix.forward.x;
	rot.y = v.x * matrix.right.y + v.y * matrix.up.y + v.z * matrix.forward.y;
	rot.z = v.x * matrix.right.z + v.y * matrix.up.z + v.z * matrix.forward.z;
	return (rot);
}
