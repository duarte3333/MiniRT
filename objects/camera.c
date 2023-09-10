#include "../includes/minirt.h"

void	rotation_x(t_vector *vec, float theta)
{
	float	temp_z;
	float	temp_y;

	temp_z = vec->z;
	temp_y = vec->y;
	vec->y = temp_y * cos(theta) + temp_z * sin(theta);
	vec->z = -temp_y * sin(theta) + temp_z * cos(theta);
}

void	rotation_y(t_vector *vec, float phi)
{
	float	temp_x;
	float	temp_z;

	temp_x = vec->x;
	temp_z = vec->z;
	vec->x = temp_x * cos(phi) + temp_z * sin(phi);
	vec->z = -temp_x * sin(phi) + temp_z * cos(phi);
}

void	rotation_z(t_vector *vec, float qsi)
{
	float	temp_x;
	float	temp_y;

	temp_x = vec->x;
	temp_y = vec->y;
	vec->x = temp_x * cos(qsi) - temp_y * sin(qsi);
	vec->y = temp_x * sin(qsi) + temp_y * cos(qsi);
}

static void rotate(t_raytracer *rt, t_camera *this, t_rotation rotation)
{
	float increment;

	increment = 0.05;
	this->theta *= ((rotation == X_theta_1) - (rotation == X_theta_2))*increment;
	rotation_x(&rt->D, this->theta);
	this->phi *= ((rotation == Y_phi_1) - (rotation == Y_phi_2))*increment;
	rotation_y(&rt->D, this->phi);
	this->qsi *= ((rotation == Z_qsi_1) - (rotation == Z_qsi_2))*increment;
	rotation_z(&rt->D, this->qsi);
}


t_camera* new_camera(char *line)
{
	t_camera *cam;

	cam = new_object(sizeof(t_camera));
	cam->type = CAMERA;
	cam->rotate = rotate;
	cam->vector.x = ft_atof(&line);
	cam->vector.y = ft_atof(&line);
	cam->vector.z = ft_atof(&line);
	cam->direction.x= ft_atof(&line);
	cam->direction.y = ft_atof(&line);
	cam->direction.z = ft_atof(&line);
	cam->fov = ft_atof(&line);
	cam->theta = 0.0f;
	cam->phi = 0.0f;
	cam->qsi = 0.0f;
	return (cam);
}
	