#include "../includes/minirt.h"

t_vector	rotation_x(t_raytracer *rt)
{
	float	temp_z;
	float	temp_y;
	t_camera *this;

	this = vars()->scene->camera;
	temp_z = rt->D.z;
	temp_y = rt->D.y;
	rt->D.y = temp_y * cos(this->theta) + temp_z * sin(this->theta);
	rt->D.z = -temp_y * sin(this->theta) + temp_z * cos(this->theta);
	return (this->vector);
}

t_vector	rotation_y(t_raytracer *rt)
{
	float	temp_x;
	float	temp_z;
	t_camera *this;

	this = vars()->scene->camera;
	temp_x = rt->D.x;
	temp_z = rt->D.z;
	rt->D.x = temp_x * cos(this->phi) + temp_z * sin(this->phi);
	rt->D.z = -temp_x * sin(this->phi) + temp_z * cos(this->phi);
	return (this->vector);
}

t_vector	rotation_z(t_raytracer *rt)
{
	float	temp_x;
	float	temp_y;
	t_camera *this;

	this = vars()->scene->camera;
	temp_x = rt->D.x;
	temp_y = rt->D.y;
	rt->D.x = temp_x * cos(this->qsi) - temp_y * sin(this->qsi);
	rt->D.y = temp_x * sin(this->qsi) + temp_y * cos(this->qsi);
	return (this->vector);
}

t_camera* new_camera(char *line)
{
	t_camera *cam;

	cam = new_object(sizeof(t_camera));
	cam->type = CAMERA;
	cam->vector.x = ft_atof(&line);
	cam->vector.y = ft_atof(&line);
	cam->vector.z = ft_atof(&line);
	cam->theta = ft_atof(&line);
	cam->phi = ft_atof(&line);
	cam->qsi = ft_atof(&line);
	return (cam);
}
	