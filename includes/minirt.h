/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:29:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/09/01 13:00:04 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "color.h"
# include "get_next_line.h"

# define BLACK 0x000000
# define WHITE 0xFFFFFF
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
typedef struct 	s_camera	t_camera;
typedef enum 	e_type		t_type;
typedef struct 	s_light		t_light;

# include "raytracer.h"
# include "parse.h"

enum e_type{
	PLANE,
	SPHERE,
	CYLINDER,
	AMBIENT,
	POINT,
	DIRECTIONAL,
	CAMERA,
	ERROR,
	EMPTY_LINE,
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
	t_object *object;
	t_object *light;
	t_object *select;
	char 	 *map_file;
};

struct 	s_object {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	float height;
	float  intensity;
};

struct 	s_camera {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
	float theta;
	float phi;
	float qsi;
};

struct 	s_light {
	t_light	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
};

struct 	s_plane {
	t_object	*next;
	t_vector direction;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
	t_vector vector;
};

struct 	s_sphere {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
	float diameter;
};

struct 	s_cylinder{
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
	float height;
	float  intensity;
	//
	t_vector axis;
	float diameter;

};

//Hook's
int			ft_key(int keycode, t_vars *vars);
int 		ft_mouse_up(int button, int x, int y, t_vars *vars);
int 		ft_mouse_down(int button, int x, int y, t_vars *vars);
int			ft_close(t_vars *vars);

//Draw
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void* 		new_object(int size);
t_object*	new_plane(char *line);
t_object* 	new_sphere(char *line);
t_object* 	new_cylinder(t_vector axis, t_vector coord, float diameter, float height, t_color color, int specular, float reflective);
t_object* 	new_camera(t_vector vector, float theta, float phi, float  qsi);

//Raytracer
void 		raytracer(t_vars *vars);
void 		canvas_to_viewport(t_raytracer *rt, float x, float y);

int 		new_trace_ray(t_object *last_obj, t_vector O, t_vector D, t_vars *vars ,t_raytracer *rt, int recursion_depth);
t_object 	*closest_intersection(t_vars* vars ,t_raytracer* rt, float t_min, float t_max);
bool 		inside(float t, float t_min, float t_max);

//Parse
int			strcmp_rt(char *a, char *extension);
int			check_map(t_vars *vars);
t_object    *parse_next(t_type type, char *line);
t_type		ft_get_type(char *line);
int			map_loading(t_vars *vars, int fd);

//Ligh
t_object 	*new_light(char *line, t_type type);
float 		compute_light(t_vars *vars, t_raytracer *rt);

//Aux
void	*ft_calloc(size_t nelem, size_t elsize);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int i);
char	*ft_strchr(const char *s, int c);
int		ft_isspace(char c);
double  ft_atof(char **line, double sig, double tmp, double frac);
void    lst_add_back(t_vars *vars, t_type type, char *line);
void    light_add_back(t_vars *vars, t_type type, char *line);


t_vector	rotation_x(t_camera *this);
t_vector	rotation_y(t_camera *this);
t_vector	rotation_z(t_camera *this);

#endif
