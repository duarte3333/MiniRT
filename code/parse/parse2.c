/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:14:16 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 18:33:42 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/* Check if the file is empty */
// int	check_empty(t_vars *vars, char *line)
// {
// 	if (line == NULL)
// 	{
// 		write (1, "Empty file. Try again please.\n", 31);
// 		ft_close (vars);
// 	}
// }

/* Verifica todas as possibilidades para que o mapa pode falhar */
int	check_map(char *map)
{
	int	fd;

	if (!strcmp_rt(map, "rt"))
	{
		write(1, "That file is not a .rt file\n", 29);
		return (-1);
	}
	else
	{
		fd = open(map, O_RDONLY);
		if (fd == -1)
			write(1, "That file is not in the repository.\n", 37);
		return (fd);
	}
	return (0);
}

int	create_scene_helper(t_scene **head, t_scene **end_scene, int fd)
{
	while (map_loading(*head, fd))
		;
	close(fd);
	if (!vars()->scene)
		vars()->scene = *head;
	else
	{
		(*end_scene)->next = *head;
		(*head)->prev = *end_scene;
	}
	*end_scene = *head;
	return (1);
}
