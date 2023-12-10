/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:26 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 17:03:32 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	strcmp_rt(char *a, char *extension)
{
	int		size;
	int		j;

	j = -1;
	size = ft_strlen(a) - (ft_strlen(extension) + 1);
	if (size < 0)
		return (0);
	while (a[++size])
	{
		if (a[size] != extension[++j])
			return (0);
	}
	return (1);
}
