#include "minirt.h"

static int	render(t_sphere *this, t_vars *vars)
{
	// t_vector O;

	// O = vector(0, 0, 0);
	// while ()
	// {

	// }
	// my_mlx_pixel_put(&vars->img, x + x1, y + y1, this->color);
	// angle += 0.1;

	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
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
	