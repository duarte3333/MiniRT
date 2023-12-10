/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:05:43 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 19:23:49 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_atof	t_atof;

//Parse
int			strcmp_rt(char *a, char *extension);
int			check_map(char *map);
t_object	*parse_next(t_type type, char *line);
t_type		ft_get_type(char *line);
int			map_loading(t_scene *scene, int fd);

//Syntax
int			check_camera(char **line);
int			check_sphere(char **line);
int			check_cone(char **line);
int			check_cylinder(char **line);
int			check_light(char **line);
int			check_ambient(char **line);
int			check_float(char **line, int g);
int			check_vector(char **line);
int			check_color(char **line);
int			check_spec_ref(char **line);
int			check_plane(char **line);

struct s_atof
{
	double	sig;
	double	tmp;
	double	frac;
	int		flag;
	double	size;
};

#endif