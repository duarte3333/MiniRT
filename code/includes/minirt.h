/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:29:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/10/10 19:23:44 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "color.h"
# include "get_next_line.h"
# include "raytracer.h"
# include "parse.h"

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define HEIGHT 1000.0f
# define WIDTH 1000.0f
# define HEIGHT_2 500.0f
# define WIDTH_2 500.0f

enum e_rotation{
	X_theta_1,
	X_theta_2,
	Y_phi_1,
	Y_phi_2,
	Z_qsi_1,
	Z_qsi_2,
};

enum e_type{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	AMBIENT,
	POINT,
	DIRECTIONAL,
	CAMERA,
	ERROR,
	EMPTY_LINE,
	COMMENT,
};

struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_scene{
	t_camera	*camera;
	t_object	*object;
	t_object	*light;
	t_object	*select;
	t_object	*select_light;
	t_object	*end;
	t_object	*end_light;
	t_scene		*next;
	t_scene		*prev;
	char		*map_file;
	int			f;
	bool		syntax;
};

struct	s_vars {
	void			*mlx;
	void			*win;
	t_data			img;
	t_scene			*scene;
	t_scene			*last;
	bool			work_all;
	int				n_threads;
	t_ray_thread	*threads;
	pthread_mutex_t	mut;
	int				count;
	t_new_objects	new_objects[8];
	int				menu;
	t_ray_thread	*rt_var;
};

struct	s_object {
	t_object	*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
};

struct	s_camera {
	t_object	*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
	t_vector	direction;
	float		fov;
};

struct	s_light {
	t_light		*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
};

struct	s_plane {
	t_object	*next;
	t_vector	direction;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
	t_vector	vector;
};

struct	s_sphere {
	t_object	*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
	float		diameter;
};

struct	s_cylinder{
	t_object	*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*resize)(int ratio);	
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
	t_vector	axis;
	float		diameter;
};

struct s_cone
{
	t_object	*next;
	t_vector	vector;
	t_type		type;
	t_color		color;
	int			specular;
	float		refletive;
	t_values	(*intersect)();
	void		(*rotate)();
	void		(*move)(int x, int y);
	void		(*resize)(int ratio);
	float		height;
	float		intensity;
	float		theta;
	float		phi;
	float		qsi;
	int			checkerboard;
	t_vector	base;
	t_vector	direction;
	t_vector	tmp;
	float		m;
	float		radius;
};

t_vars		*vars(void);

//Syntax
int			test_syntax(char *str);

//Hook's
int			ft_key(int keycode);
int			ft_mouse_down(int button, int x, int y);
int			ft_close(t_vars *vars);
void		threads_update(void);
void		light_keys(int keycode);

//Objects
void		*new_object(int size);
t_object	*new_plane(char *line);
t_object	*new_sphere(char *line);
t_object	*new_cylinder(char *line);
t_object	*new_cone(char *line);
t_camera	*new_camera(char *line);

//Camera
void		rotation_x(t_vector *vec, float theta);
void		rotation_y(t_vector *vec, float theta);
void		rotation_z(t_vector *vec, float theta);

//Ligh
t_object	*new_light(char *line, t_type type);
float		*compute_light(t_raytracer *rt);
void		light_prepare(t_raytracer *rt, t_object *obj);
int			point_and_directional_light(t_raytracer *rt, t_object **tmp);
void		ambient_light(t_raytracer *rt, t_object *tmp);

//Raytracer
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void		raytracer_threads(t_ray_thread *thread);
void		raytracer(t_scene *scene);
void		canvas_to_viewport(t_raytracer *rt, float x, float y);
int			new_trace_ray(t_object *last_obj, t_raytracer rt, \
	int recursion_depth, float limit);
t_object	*closest_intersection(t_raytracer *rt, t_vector limits);
bool		inside(float t, float t_min, float t_max);
void		choose_normal(t_raytracer *rt, t_object *obj);
t_vector	reflected_ray(t_vector R, t_vector N);
t_object	*checkerboard(t_raytracer *rt, t_object *obj);


//Threads
int			ft_init_threads(void);
int			ft_join_threads(t_vars *vars);
void		*routine(void *arg);

//Paint
void		paint(void);

//Aux
void		*ft_calloc(size_t nelem, size_t elsize);
char		*get_next_line(int fd);
int			ft_strlen(const char *str);
int			ft_isdigit(int i);
int			ft_isspace(char c);
double		ft_atof(char **line);
void		lst_add_back(t_scene *scene, t_type type, char *line);
void		light_add_back(t_scene *scene, t_type type, char *line);

//Free
void		free_objects(t_scene *head);
void		free_array(char **arr);

//Menu
void		ft_menu(void);








#endif
