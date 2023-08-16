#include "minirt.h"

int	ft_close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	render(t_vars *vars)
{
	int		y;
	int		x;

	y = 0;	
	x = 5;
	while (y < 10)
	{
		draw_painting(vars, &vars->img, 5, y);
		y++;
	}

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.img.img = mlx_new_image(vars.mlx, 500, 500);
	vars.img.addr = mlx_get_data_addr(vars.img.img, \
		&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, ft_close, &vars);
	mlx_loop_hook(vars.mlx, render, &vars);	
	mlx_loop(vars.mlx);
}