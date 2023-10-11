/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:57 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 00:46:49 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

t_vars	*vars(void)
{
	static t_vars	my_vars;

	return (&my_vars);
}

static void	init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->menu = 0;
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Dudu Raytracer :)");
	mlx_hook(vars->win, 17, 0, ft_close, vars);
	mlx_hook(vars->win, 2, 1L << 0, ft_key, NULL);
	mlx_hook(vars->win, 4, 1L << 2, ft_mouse_down, NULL);
}

	// if (!test_syntax(arg))
	// {
	// 	free(head);
	// 	close(fd);
	// 	return (0);
	// } acima head
static int	create_scene(char *arg)
{
	int				fd;
	static t_scene	*end_scene;
	t_scene			*head;

	head = ft_calloc(sizeof(t_scene), 1);
	head->map_file = arg;
	fd = check_map(arg);
	if (fd == -1)
	{
		free(head);
		return (0);
	}
	vars()->last = head;
	while (map_loading(head, fd))
		;
	close(fd);
	if (!vars()->scene)
		vars()->scene = head;
	else
	{
		end_scene->next = head;
		head->prev = end_scene;
	}
	end_scene = head;
	return (1);
}

static void	init_creations(void)
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
		vars()->work_all = true;
		init_creations();
		i = 0;
		while (av[++i])
		{		
			if (!create_scene(av[i]))
				printf("Bad Map: %s\n", av[i]);
		}
		if (vars()->scene == NULL)
			return (0);
		init_window(vars());
		vars()->n_threads = sysconf(_SC_NPROCESSORS_ONLN) - 4;
		if (ft_init_threads() == -1)
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
//Problem de overflow das cores DONE
//Otimizar last do vars -
//Meter check syntax - DONE
//Problema do planes - DONE
//Como meter FOV - DONE
//Resolver problema plano - DONE
//Ver rotacoes camara - DONE
//Direcao da camera DONE
//Direcao pos rotacao DONE
//Meter mapas fixes a dar DONE
//Situacao de threads nao esta bem DONE
//Rotacoes cilindro e do cone incorretas DONE

//BONUS
//Fazer cone DONE
//Fazer phong model DONE
//Fazer luzes com varias cores DONE
//Fazer checkboard - 
//Fazer texturas DONE
//Reflections DONE
//Mudar mapa em tempo real DONE
//Fazer menu DONE 
//Multi-threading DONE

//REVISAO FINAL
//Rotacao cone meh
//Tester mapas falhados
//Leaks
//Folha de avaliacao
//AMANHA
//Check syntax checking - 
//norm check pc's

//CASA
//Ver bases do cone e cilindro -