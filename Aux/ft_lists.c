#include "../includes/minirt.h"

void    lst_add_back(t_scene *scene,t_type type, char *line)
{
    t_object *new;
    
    new = parse_next(type, line);
    if (scene->object == NULL)
        scene->object = new;
    else
        scene->end->next = new;
    scene->end = new;
}

void    light_add_back(t_scene *scene, t_type type, char *line)
{
    t_object *new;
    
    new = parse_next(type, line);
    if (scene->light == NULL)
        scene->light = new;
    else
        scene->end_light->next = new;
    scene->end_light = new;
}