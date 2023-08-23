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

// t_type ft_get_type(char* line)
// {
// 	if (line[0] == 'A')
// 		return AMBIENT;
// 	if (line[0] == 'L')
// 		return POINT;
// 	if (line[0] == 's' && line[1] == 'p') 
// 		return SPHERE;
// 	if (line[0] == 'p' && line[1] == 'l') 
// 		return PLANE;
// 	if (line[0] == 'c' && line[1] == 'y') 
// 		return CYLINDER;
// 	if (line[0] == '\n')
// 		return EMPTY_LINE;
// 	return ERROR;
// }

// t_type ft_check_line(char *line)
// {
// 	int 	i;
// 	t_type type;

// 	i = 0;
// 	type = ft_get_type(line);
// 	if (type >= 0 && type <= 2)
// 		i++;
// 	while (line && line[++i])
// 	{
// 		if (!line[i] && !ft_isdigit(line[i]) && line[i] != '.' && line[i] != ',')
// 			return ERROR;
// 	}
// 	return type;
// }
// void	map_loading(t_vars *vars, int fd, int index)
// {
// 	char	*line;
// 	t_object *obj;
// 	t_t
// // 	line = get_next_line(fd);
// 	line = get_next_line(fd);
// 	ft_check_line(line, obj)
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