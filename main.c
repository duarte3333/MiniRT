#include "includes/minirt.h"

void init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->	//vars->objects[0] = new_object(sizeof(t_object));
	img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_hook(vars->win, 17, 0, ft_close, vars);
	mlx_hook(vars->win, 2, 1L<<0, ft_key, vars);
	mlx_hook(vars->win, 4, 1L<<2, ft_mouse_down, vars);
	mlx_hook(vars->win, 5, 1L<<3, ft_mouse_up, vars);

	//mlx_hook(vars.win, 2, 1L<<0, ft_select, &vars);
}

int	main(int ac, char **av)
{
	t_vars *vars;
	int fd;

	if (ac == 2)
	{
		vars = (t_vars*)calloc(sizeof(t_vars), 1);
		// vars->map_file = av[1];
		// fd = check_map(vars);

		//objects
		//vars.objects[] = new_plane(vector(2, 0, 4), vector(-2.64, 20.6, 2.58), 0x00FFFF);
		//vars->objects[3] = new_plane(vector(2, 0, 4), vector(0, 18.15, 2.88), color(255, 255, 0));
		vars->objects[0] = new_sphere(vector( 0, -1, 3), 2.0f, color(255, 0, 0), 500, 0.2);
		vars->objects[1] = new_sphere(vector( 2, 0, 4), 2.0f, color(0, 0, 255), 500, 0.3);
		vars->objects[2] = new_sphere(vector(-2, 0, 4), 2.0f, color(0, 255, 0), 10, 0.4);
		vars->objects[3] = new_sphere(vector(0, -5001, 0), 10000.0f, color(255, 255, 0), 1000, 0.5);
		//light
		vars->lights[0] = new_light(0.3, vector(0, 0, 0), AMBIENT);
		vars->lights[1] = new_light(0.3, vector(2, 1, 0), POINT);
		vars->lights[2] = new_light(0.3, vector(1, 4, 4), DIRECTIONAL);
		init_window(vars);
		mlx_loop_hook(vars->mlx, raytracer, vars);	
		//raytracer(&vars);
		mlx_loop(vars->mlx);
		//free(vars);
	}
	else
		write(1, "Not enough arguments\n", 22);
}