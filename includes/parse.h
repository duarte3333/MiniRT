#ifndef VECTOR_H
# define VECTOR_H

//Parse
int			strcmp_rt(char *a, char *extension);
int			check_map(t_vars *vars);
t_object    *parse_next(t_type type, char *line);
t_type		ft_get_type(char *line);
int			map_loading(t_vars *vars, int fd);


#endif