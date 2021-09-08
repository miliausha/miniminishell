#include "libft.h"

void	ft_strcpy(char *dst, const char *src)
{
	int		i;
	char	*d;

	d = dst;
	i = 0;
	while (src[i])
	{
		d[i] = src[i];
		i++;
	}
	d[i] = '\0';
}
