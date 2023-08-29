/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:29:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/08/30 00:39:39 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "color.h"
# include "get_next_line.h"

# define WHITE 0x000000
# define HEIGHT 1000.0f
# define WIDTH 1000.0f
# define HEIGHT_2 500.0f
# define WIDTH_2 500.0f

typedef struct  s_data		t_data;
typedef struct	s_vars		t_vars;
typedef struct 	s_object	t_object;
typedef struct 	s_plane 	t_plane;
typedef struct 	s_sphere	t_sphere;
typedef struct 	s_cylinder	t_cylinder;
typedef enum 	e_type		t_type;
typedef struct 	s_light		t_light;

# include "raytracer.h"

enum e_type{
	PLANE,
	SPHERE,
	CYLINDER,
	AMBIENT,
	POINT,
	DIRECTIONAL,
	ERROR,
	EMPTY_LINE
};

struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	 img;
	//t_object **objects;
	t_object *objects[6];
	//t_light  **lights;
	t_light  *lights[4];
	t_object *select;
	char 	 *map_file;
	// int	 nb_objs;
	// int 	 nb_lights;
};

struct 	s_object {
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
};

struct 	s_light {
	t_vector position;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
	//
	float  intensity;
};

struct 	s_plane {
	t_vector direction;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	//
	t_vector vector;
};

struct 	s_sphere {
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	//
	float diameter;
};

struct 	s_cylinder{
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
	//
	t_vector axis;
	float diameter;
	float height;

};

//Hook's
int			ft_key(int keycode, t_vars *vars);
int 		ft_mouse_scroll(int button, int x, int y, t_vars *vars);
int 		ft_mouse_up(int button, int x, int y, t_vars *vars);
int 		ft_mouse_down(int button, int x, int y, t_vars *vars);
int			ft_close(t_vars *vars);

//Draw
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void* 		new_object(int size);
t_object*	new_plane(t_vector coord, t_vector v, t_color color, int specular, float reflective);
t_object* 	new_sphere(t_vector coord, float diameter, t_color color, int specular, float reflective);
t_object* 	new_cylinder(t_vector axis, t_vector coord, float diameter, float height, t_color color, int specular, float reflective);

//Raytracer
void 		raytracer(t_vars *vars);
void 		canvas_to_viewport(t_raytracer *rt, float x, float y);
t_object 	*trace_ray(t_vector O, t_vector D, t_vars* vars ,t_raytracer* rt, float t_min, float t_max, int recursion_depth);
t_object 	*closest_intersection(t_vars* vars ,t_raytracer* rt, float t_min, float t_max);
bool 		inside(float t, float t_min, float t_max);

//Light
t_light 	*new_light(float intensity, t_vector pos, t_type type);
float 		compute_light(t_vars *vars, t_raytracer *rt);

//Parse
void	map_loading(t_vars *vars, int fd, int index);
int		strcmp_rt(char *a, char *extension);
int		check_map(t_vars *vars);

//Aux
void	*ft_calloc(size_t nelem, size_t elsize);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int i);
char	*ft_strchr(const char *s, int c);

#endif
