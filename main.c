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
	//mlx_hook(vars->win, 5, 1L<<3, ft_mouse_up, vars);
}

int	main(int ac, char **av)
{
	static t_vars vars;
	int fd;

	if (ac == 2)
	{
		//vars = (t_vars*)calloc(sizeof(t_vars), 1);
		vars.map_file = av[1];
		fd = check_map(&vars);
		while (map_loading(&vars, fd))
			;
		close(fd);
		init_window(&vars);
		mlx_loop_hook(vars.mlx, raytracer, &vars);	
		//raytracer(&vars);
		mlx_loop(vars.mlx);
		//free(vars);
	}
	else
		write(1, "Not enough arguments\n", 22);
}