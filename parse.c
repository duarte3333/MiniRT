#include "includes/minirt.h"

t_object    *parse_next(t_type type, char *line)
{
    if (type == PLANE)
        return (new_plane(line));
    if (type == SPHERE)
        return (new_sphere(line));
    if (type == CYLINDER)
        return (new_cylinder(line));
    if (type == AMBIENT)
        return (new_light(line, type));
    if (type == DIRECTIONAL)
        return (new_light(line, type));
	if (type == POINT)
        return (new_light(line, type));
	else
		return (NULL);
}

t_type ft_get_type(char *line)
{
	if (line)
    {
        if (line[0] == '\n')
            return EMPTY_LINE;
        if (line[0] == 'A')
            return AMBIENT;
        if (line[0] == 'P')
            return POINT;   
		if (line[0] == 'D')
            return DIRECTIONAL; 
		if (line[0] == 'C')
            return CAMERA;
        if ((line)[0] == 's' && (line)[1] == 'p') 
            return SPHERE;
        if ((line)[0] == 'p' && (line)[1] == 'l') 
            return PLANE;
        if ((line)[0] == 'c' && (line)[1] == 'y') 
            return CYLINDER;
    }
	return ERROR;
}

void ft_check_line(t_scene *scene, char *line)
{
	int 	i;
	t_type type;

	i = 0;
	type = ft_get_type(line);
	if (type >= 0 && type <= 2)
		i++;
	while (line && line[++i])
	{
		if (!line[i] && !ft_isdigit(line[i]) && line[i] != '.' && line[i] != ',')
			return ;
	}
    i = 0;
    while (line[i] && !ft_isdigit(line[i]) && line[i] != '+' && line[i] != '-')
        i++;
	if (type == CAMERA)
		scene->camera = new_camera(line);
	else if ((type != AMBIENT) && (type != POINT) && (type != DIRECTIONAL))
		lst_add_back(scene, type, (line + i));
	else
		light_add_back(scene, type, (line + i));
}

int	map_loading(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (0);	
	ft_check_line(scene, line);
	free(line);
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
int	check_map()
{
	int	fd;
	int i;

	i = 0;
	if (!strcmp_rt(vars()->map_file, "rt"))
	{
		write(1, "That file is not a .rt file\n", 29);
		ft_close(vars());
	}
	else
	{
		fd = open(vars()->map_file, O_RDONLY);
		if (fd == -1)
		{
			write(1, "That file is not in the repository.\n", 37);
			ft_close (vars);
		}
		//check_empty(vars, get_next_line(fd));
		return (fd);
	}
	return (0);
}


