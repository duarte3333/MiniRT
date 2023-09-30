#include "../includes/minirt.h"

static int	check_camera(char **line)
{
	(*line)++;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_sphere(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
    if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_cone(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_cylinder(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_float(line, 1) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_light(char **line)
{
	(*line)++;
	if (check_vector(line) == 0)
		return (0);
	if (check_float(line, 0) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_ambient(char **line)
{
	(*line)++;
	if (check_float(line, 0) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int		check_float(char **line, int g)
{
	int	f;

	f = 0;
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line) && **line != '+' && g == 1 && **line != '-')
		return (0);
    (*line)++;
	while (**line && **line != ',' && !ft_isspace(**line))
	{
		if (**line == '.' && f == 0)
			f = 1;
		else if (**line == '.' && f == 1)
			return (0);
		else if (!ft_isdigit(**line) && **line != '.')
			return (0);
		(*line)++;
	}
	return (1);
}

int		check_vector(char **line)
{
	if (check_float(line, 1) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 1) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 1) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int		check_color(char **line)
{
	if (check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 0) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int     check_spec_ref(char **line)
{
    if (check_float(line, 0) == 0)
		return (0);
    if (check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
    return (1);
}

int		check_plane(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0)
		return (0);
	if (check_vector(line) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
    if (check_spec_ref(line) == 0)
        return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

static int	check_repeat(t_type type)
{
	if (type == CAMERA && vars()->last->f == 0)
		vars()->last->f = 1;
	else if (type == CAMERA && vars()->last->f == 1)
		return (0);
	return (1);
}

static void	test_syntax_helper(char **line, char **head, int fd)
{
	free(*head);
	*line = get_next_line(fd);
	*head = *line;
}

static int test_objects(char *line)
{
	t_type type;

	type = ft_get_type(line);
	if (check_repeat(type) == 0)
			return (0);
	if (type == PLANE && !check_plane(&line))
		return (0);
	else if (type == SPHERE && !check_sphere(&line))
		return (0);
	else if (type == AMBIENT && !check_ambient(&line))
		return (0);
	else if (type == CONE && !check_cone(&line))
		return (0);
	else if (type == CYLINDER && !check_cylinder(&line))
		return (0);
	else if (type == CAMERA && !check_camera(&line))
		return (0);
	else if ((type == POINT || type == DIRECTIONAL) && !check_light(&line))
		return (0);
	else if (type == ERROR)
		return (0);
	return (1);
}

int		test_syntax(char *str)
{
	int fd;
	char *line;
	char *head;

	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	head = line;
	while (line != NULL)
	{
		if (!test_objects(line))
		{
			while (line != NULL)
				line = get_next_line(fd);
			close(fd);
			free(head);
			return (0);
		}
		test_syntax_helper(&line, &head, fd);
	}
	close(fd);
	free(head);
	if (vars()->last->f == 0)
		return (0);
	return (1);
}