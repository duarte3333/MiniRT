#include "includes/minirt.h"

t_vars *vars()
{
	static t_vars my_vars;
	return (&my_vars);
}

void init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->	//vars->objects[0] = new_object(sizeof(t_object));
	img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_hook(vars->win, 17, 0, ft_close, vars);
	mlx_hook(vars->win, 2, 1L<<0, ft_key, NULL);
	mlx_hook(vars->win, 4, 1L<<2, ft_mouse_down, NULL);
	//mlx_hook(vars->win, 5, 1L<<3, ft_mouse_up, vars);
}

int create_scene(char *arg)
{
	int fd;
	static t_scene *end_scene;
	t_scene *head;

	head = ft_calloc(sizeof(t_scene), 1);
	vars()->map_file = arg;
	fd = check_map();
	if (fd == -1)
	{
		printf("Error openning the file!");
		return 3;
	}
	while (map_loading(head, fd))
		;
	close(fd);
	if (!vars()->scene)
		vars()->scene = head;
	else 
		end_scene->next = head;
	end_scene = head;
	return 0;
}

int	main(int ac, char **av)
{

	int i;
	i = 0;
	if (ac == 2)
	{
		//vars = (t_vars*)calloc(sizeof(t_vars), 1);
		while (av[++i])
			create_scene(av[i]);
		init_window(vars());
		mlx_loop_hook(vars()->mlx, raytracer, NULL);	
		//raytracer(&vars);
		mlx_loop(vars()->mlx);
		//free(vars);
	}
	else
		write(1, "Not enough arguments\n", 22);
}