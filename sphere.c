#include "minirt.h"

static int	render(t_object *this, t_vars *vars)
{
	double 	y, x;
	double	r;
	double 	angle;
	double		x1, y1;
	static const double PI = 3.1415926535;

	y = this->vector.y;	
	x = this->vector.x;
	r = 50;
	angle = 0;
	//radianos para graus -> PI / 180
	while (r > 0)
	{
		angle = 0;
		while (angle < 360)
		{
			x1 = r * cos(angle * PI / 180);
			y1 = r * sin(angle * PI / 180);
			my_mlx_pixel_put(&vars->img, x + x1, y + y1, this->color);
			angle += 0.1;
		}
		r -= 0.1;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

t_object* new_sphere(t_vector coord, float diameter, int color)
{
	t_sphere *sphere;

	sphere = new_object(sizeof(t_sphere));
	sphere->render = render;
	sphere->shape = SPHERE;
	sphere->vector = coord;
	sphere->color = color;
	sphere->diameter = diameter;
	return ((t_object *)sphere);
}
	