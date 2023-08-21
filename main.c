#include "minirt.h"

int	main(void)
{
	static t_vars vars;

	//vars.objects[0] = new_object(sizeof(t_object));
	vars.objects[0] = new_sphere(vector( 0,-1, 4), 1.0f, 0xFF0000);
	vars.objects[1] = new_sphere(vector( 2, 0, 4), 1.0f, 0x00FF00);
	vars.objects[2] = new_sphere(vector(-2, 0, 4), 1.0f, 0x0000FF);
	//vars.objects[0] = new_sphere(vector(100, 100, 4), 1, 0x3bff00);
	//vars.objects[1] = new_sphere(vector(250, 250, 4), 1, 0xee00ff);
	//vars.objects[2] = new_sphere(vector(250, 250, 4), 1, 0xee00ff);
	//vars.objects[2] = new_plane(vector(300, 180, 4),vector(100, 180, 4), 0xfa0000);


	vars.mlx = mlx_init();
	vars.img.img = mlx_new_image(vars.mlx, 500, 500);
	vars.img.addr = mlx_get_data_addr(vars.img.img, \
		&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello world!");
	
	mlx_hook(vars.win, 2, 1L<<0, ft_close, &vars);
	//mlx_loop_hook(vars.mlx, ft_render, &vars);	
	ft_render(&vars);
	mlx_loop(vars.mlx);
}