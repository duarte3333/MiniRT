#include "includes/minirt.h"

// int	*split_array(t_vars *vars, char *line)
// {
// 	int		*t;
// 	char	**temp;
// 	char	**property;
// 	int		size;
// 	int		i;

// 	i = 0;
// 	temp = ft_split(line, ' ');
// 	property = ft_split(temp, ',');
// 	vars->objects[i] = ft_calloc(sizeof(t_object), 1);
// 	return (t);
// }

// void	map_loading(t_vars *vars, int fd, int index)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	if (line[0] == 'A' || line[0] == 'L')
// 		vars->nb_lights++;
// 	else if ( (line[0] == 's' && line[1] == 'p') || \
// 			  (line[0] == 'p' && line[1] == 'l') || \
// 			  (line[0] == 'c' && line[1] == 'y'))
// 		vars->nb_objs++;
// 	if (line)
// 		map_loading(vars, fd, index + 1);
// 	else
// 	{
// 		vars->objects = (t_object **)ft_calloc(sizeof(t_object*) * vars->nb_objs, 1);
// 		vars->lights = (t_object **)ft_calloc(sizeof(t_object*) * vars->nb_lights, 1);
// 	}
// 	if (line)
// 		vars->objects[index] = split_array(vars, line);
// 	else
// 		vars->objects[index] = NULL;
// 	free(line);
// }

int	strcmp_rt(char *a, char *extension)
{
	int		size;
	int		j;

	j = -1;
	size = ft_strlen(a) - (ft_strlen(extension) + 1);
	if (size < 0)
		return 0;
	while (a[++size])
	{
		if (a[size] != extension[++j])
			return (0);
	}
	return (1);
}

/* Check if the file is empty */
int	check_empty(t_vars *vars, char *line)
{
	if (line == NULL)
	{
		write (1, "Empty file. Try again please.\n", 31);
		ft_close (vars);
	}
}

/* Verifica todas as possibilidades para que o mapa pode falhar */
int	check_map(t_vars *vars)
{
	int	fd;
	int i;

	i = 0;
	if (!strcmp_rt(vars->map_file, "rt"))
	{
		write(1, "That file is not a .rt file\n", 29);
		ft_close(vars);
	}
	else
	{
		fd = open(vars->map_file, O_RDONLY);
		if (fd == -1)
		{
			write(1, "That file is not in the repository.\n", 37);
			ft_close (vars);
		}
		check_empty(vars, get_next_line(fd));
		return (fd);
	}
	return (0);
}