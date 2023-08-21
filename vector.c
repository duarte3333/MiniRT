#include "minirt.h"

t_vector vector(float x, float y, float z){
	return ((t_vector){x, y, z});
}

t_vector vector_operation(t_vector vec, t_vector center)
{
	vec.x -= center.x;
	vec.y -= center.y;
	vec.z -= center.z;
	return (vec);
}

float dot(t_vector va, t_vector vb)
{
	return ((va.x)*(vb.x) + (va.y)*(vb.y) + (va.z)*(vb.z));
}