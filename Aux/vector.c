#include "../includes/minirt.h"

t_vector vector(float x, float y, float z){
	return ((t_vector){x, y, z});
}

t_vector vector_subtract(t_vector vec, t_vector vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}

t_vector vector_add(t_vector vec, t_vector vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

t_vector vector_multiply(t_vector vec, t_vector vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

t_vector vector_divide(t_vector vec, t_vector vec2)
{
	vec.x /= vec2.x;
	vec.y /= vec2.y;
	vec.z /= vec2.z;
	return (vec);
}

float dot(t_vector va, t_vector vb)
{
	return ((va.x)*(vb.x) + (va.y)*(vb.y) + (va.z)*(vb.z));
}

float module(t_vector vec)
{
	return (sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z));
}