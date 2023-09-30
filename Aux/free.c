#include "../includes/minirt.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free (arr[i++]);
	free (arr);
}

static void erase_object(t_object *obj)
{
	t_object *obj_tmp;

	while (obj)
	{
		obj_tmp = obj;
		obj = obj->next;
		free(obj_tmp);
	}
}

void free_objects(t_scene *head)
{
	t_scene	 *scene;

	while (head)
	{
		scene = head;
		head = head->next;
		erase_object(scene->object);
		erase_object(scene->light);
		free(scene->camera);
		free(scene);
	}
}