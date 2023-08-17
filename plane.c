#include "minirt.h"

static int	render(t_plane *this, t_vars *vars)
{
	int y;
	int x;

	y = -1;	
	//radianos para graus -> PI / 180
	while (++y < 100)
	{
		x = -1;
		while (++x < 100)
		{
			my_mlx_pixel_put(&vars->img, x + 100, y + 100, this->color);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

t_object* new_plane(t_vector coord, t_vector direction, int color)
{
	t_plane *plane;

	plane = new_object(sizeof(t_plane));
	plane->render = render;
	plane->shape = PLANE;
	plane->vector = coord;
	plane->color = color;
	plane->direction = direction;
	return ((t_object *)plane);
}
	