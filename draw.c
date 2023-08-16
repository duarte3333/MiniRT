#include "minirt.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (color == -16777216)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	my_mlx_pixel_get(t_data *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}

// void 	clean_img(t_vars *vars)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < vars->max_x)
// 	{
// 		j = -1;
// 		while (++j < vars->max_y)
// 			my_mlx_pixel_put(&vars->painting, i, j, 0x00000000);
// 	}
// }

void	draw_painting(t_vars *vars, t_data *img, int x1, int y1)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 500)
	{
		x = -1;
		while (++x < 500)
		{
			my_mlx_pixel_put(&vars->img, x1 + x, y1 + y, \
			my_mlx_pixel_get(img, x, y));
		}
	}
}

// void	draw_resize_img(t_vars *vars, t_img *img, double w, double h, int x, int y)
// {
// 	double	i;
// 	double	j;

// 	//y = -1;
// 	i = 0;
// 	while (++y < h)
// 	{
// 		//x = -1;
// 		j = 0;
// 		while (++x < w)
// 		{	
// 			my_mlx_pixel_put(&vars->painting, x, y, \
// 			my_mlx_pixel_get(img, j, i));
// 			j += (img->width / w);
// 		}
// 		i += (img->height / h);
// 	}
// }