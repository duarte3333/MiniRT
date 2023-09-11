#include "includes/minirt.h"

t_vars *vars()
{
	static t_vars my_vars;
	return (&my_vars);
}

static void init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->	//vars->objects[0] = new_object(sizeof(t_object));
	img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Dudu Raytracer :)");
	mlx_hook(vars->win, 17, 0, ft_close, vars);
	mlx_hook(vars->win, 2, 1L<<0, ft_key, NULL);
	mlx_hook(vars->win, 4, 1L<<2, ft_mouse_down, NULL);
	//mlx_hook(vars->win, 5, 1L<<3, ft_mouse_up, vars);
}

static int create_scene(char *arg)
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
		return 1;
	}
	while (map_loading(head, fd))
		;
	close(fd);
	if (!vars()->scene)
		vars()->scene = head;
	else 
		end_scene->next = head;
	end_scene = head;
	return head->syntax;
}

static void init_creations()
{
	vars()->new_objects[PLANE] = new_plane;
	vars()->new_objects[SPHERE] = new_sphere;
	vars()->new_objects[CYLINDER] = new_cylinder;
	vars()->new_objects[CONE] = new_cone;
	vars()->new_objects[AMBIENT] = new_light;
	vars()->new_objects[POINT] = new_light;
	vars()->new_objects[DIRECTIONAL] = new_light;
	vars()->new_objects[CAMERA] = new_camera;
}

int	main(int ac, char **av)
{
	int	i;

	if (ac >= 2)
	{
		init_creations();
		i = 0;
		while (av[++i])
		{			
			if (create_scene(av[i]) )
				printf("Bad Map: %s\n", av[i]);
		}
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

//Verificar calloc e bzero DONE
//Fazer camara mexer e rodar(criar camara) DONE
//Checker se existe camara DONE
//Corrigir SEGV no parsing DONE
//Meter check syntax


//Ver rotacoes camara AFONSO
//Ver bases do cone e cilindro AFONSO

//BONUS
//Fazer cone DONE
//Fazer checkboard
//Fazer texturas
//Fazer luzes com varias cores