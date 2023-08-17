#include "minirt.h"

t_vector vector(int x, int y, int z){
	return ((t_vector){x, y, z});
}
int	main(void)
{
	static t_vars vars;
	t_vector vecSphere;

	vecSphere = vector(100, 110.0, 20.6);
	vars.objects[0] = new_object(sizeof(t_object));
	vars.objects[1] = new_sphere(vecSphere, 5, 0xff5c0a);

	vars.mlx = mlx_init();
	vars.img.img = mlx_new_image(vars.mlx, 500, 500);
	vars.img.addr = mlx_get_data_addr(vars.img.img, \
		&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello world!");
	
	mlx_hook(vars.win, 2, 1L<<0, ft_close, &vars);
	mlx_loop_hook(vars.mlx, ft_render, &vars);	
	mlx_loop(vars.mlx);
}