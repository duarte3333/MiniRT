#include "../includes/minirt.h"

int	strcmp_rt(char *a, char *extension)
{
	int		size;
	int		j;

	j = -1;
	size = ft_strlen(a) - (ft_strlen(extension) + 1);
	if (size < 0)
		return 0;
	while (a[++size])
	{
		if (a[size] != extension[++j])
			return (0);
	}
	return (1);
}