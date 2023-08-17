#include "minirt.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (color == -16777216)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	ft_render(t_vars *vars)
{
	vars->objects[0]->render(vars->objects[0], vars);
	vars->objects[1]->render(vars->objects[1], vars);
	return (0);
}