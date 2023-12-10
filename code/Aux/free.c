/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:22:58 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/12 20:24:45 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free (arr[i++]);
	free (arr);
}

static void	erase_object(t_object *obj)
{
	t_object	*obj_tmp;

	while (obj)
	{
		obj_tmp = obj;
		obj = obj->next;
		free(obj_tmp);
	}
}

void	free_objects(t_scene *head)
{
	t_scene	*scene;

	while (head)
		head = head->prev;
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
