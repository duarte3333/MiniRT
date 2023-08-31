#include "includes/minirt.h"

t_vector	rotation_x(t_camera *this)
{
	float	temp_z;
	float	temp_y;

	temp_z = this->vector.z;
	temp_y = this->vector.y;
	this->vector.y = temp_y * cos(this->theta) + temp_z * sin(this->theta);
	this->vector.z = -temp_y * sin(this->theta) + temp_z * cos(this->theta);
	return (this->vector);
}

t_vector	rotation_y(t_camera *this)
{
	float	temp_x;
	float	temp_z;

	temp_x = this->vector.x;
	temp_z = this->vector.z;
	this->vector.x = temp_x * cos(this->phi) + temp_z * sin(this->phi);
	this->vector.z = -temp_x * sin(this->phi) + temp_z * cos(this->phi);
	return (this->vector);
}

t_vector	rotation_z(t_camera *this)
{
	float	temp_x;
	float	temp_y;

	temp_x = this->vector.x;
	temp_y = this->vector.y;
	this->vector.x = temp_x * cos(this->qsi) - temp_y * sin(this->qsi);
	this->vector.y = temp_x * sin(this->qsi) + temp_y * cos(this->qsi);
	return (this->vector);
}

t_object* new_camera(t_vector vector, float theta, float phi, float  qsi)
{
	t_camera *cam;

	cam = new_object(sizeof(t_camera));
	cam->type = CAMERA;
	cam->vector = vector;
	cam->theta = theta;
	cam->phi = phi;
	cam->qsi = qsi;
	return ((t_object *)cam);
}
	