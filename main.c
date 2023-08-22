#include "minirt.h"

int	main(void)
{
	static t_vars vars;

	//objects
	vars.objects[0] = new_plane(vector(2, 0, 4), vector(0, 18.15, 2.88), 0xFFFF00);
	vars.objects[1] = new_plane(vector(2, 0, 4), vector(-2.64, 20.6, 2.58), 0x00FFFF);
	vars.objects[2] = new_sphere(vector( 0, -1, 3), 2.0f, 0xFF0000);
	vars.objects[3] = new_sphere(vector( 2, 0, 4), 2.0f, 0x0000FF);
	vars.objects[4] = new_sphere(vector(-2, 0, 4), 2.0f, 0x00FF00);
	//light
	vars.lights[0] = new_light();
	vars.mlx = mlx_init();
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, \
		&vars.	//vars.objects[0] = new_object(sizeof(t_object));
img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	
	mlx_hook(vars.win, 2, 1L<<0, ft_key, &vars);
	mlx_hook(vars.win, 4, 1L<<2, ft_mouse_down, &vars);
	mlx_hook(vars.win, 5, 1L<<3, ft_mouse_up, &vars);

	//mlx_hook(vars.win, 2, 1L<<0, ft_select, &vars);

	mlx_loop_hook(vars.mlx, ft_render, &vars);	
	//ft_render(&vars);
	mlx_loop(vars.mlx);
}