#ifndef PARSE_H
# define PARSE_H

typedef struct  s_atof 	 t_atof;

//Parse
int			strcmp_rt(char *a, char *extension);
int			check_map();
t_object    *parse_next(t_type type, char *line);
t_type		ft_get_type(char *line);
int			map_loading(t_scene *scene, int fd);

struct s_atof
{
	double sig;
	double tmp;
	double frac;
	int flag;
	double size;
};



#endif