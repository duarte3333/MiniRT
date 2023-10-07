#include "../includes/minirt.h"

t_camera* new_camera(char *line)
{
	t_camera *cam;

	cam = new_object(sizeof(t_camera));
	cam->type = CAMERA;
	//cam->rotate = rotate;
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
	