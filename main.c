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
		return -1;
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

void paint_chunk(t_ray_thread *thread)
{
	t_chunk s;

	s.sx = 0;
    s.x = thread->x_i - 1;
	pthread_mutex_lock(&thread->th_mut);
	while (++s.x < thread->x_f)
	{
        s.sy = 0;
        s.y = -HEIGHT_2 - 1;
		while (++s.y < HEIGHT_2)
			my_mlx_pixel_put(&vars()->img, s.x + WIDTH_2, \
				s.y + HEIGHT_2, thread->color[s.sy++ * thread->delta + s.sx]);
        s.sx++;
	}
	pthread_mutex_unlock(&thread->th_mut);
}

void paint()
{
	int	n;

	pthread_mutex_lock(&vars()->mut);
    if (vars()->count != vars()->n_threads)
	{
		pthread_mutex_unlock(&vars()->mut);
		return ;
	}
	vars()->count = 0;
	n = -1;
	while (++n < vars()->n_threads)
		paint_chunk(&vars()->threads[n]);
	pthread_mutex_unlock(&vars()->mut);
	mlx_put_image_to_window(vars()->mlx, vars()->win, vars()->img.img, 0, 0);

}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 2)
	{
		while (av[++i])
			create_scene(av[i]);
		init_window(vars());
		vars()->n_threads = sysconf(_SC_NPROCESSORS_ONLN) - 4;
		if(ft_init_threads() == -1)
			return (-1);
		mlx_loop_hook(vars()->mlx, paint, NULL);
		mlx_loop(vars()->mlx);
		pthread_mutex_destroy(&vars()->mut);
		free(vars()->threads);
	}
	else
		write(1, "Not enough arguments\n", 22);
}

//Verificar calloc e bzero
//Fazer camara mexer e rodar(criar camara)
//Fazer cilindro
//Meter check syntax
//Corrigir SEGV no parsing

//BONUS
//Fazer cone
//Fazer checkboard
//Fazer texturas
//Fazer luzes com varias cores