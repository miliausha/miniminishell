/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:49:35 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/02 19:49:36 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = ft_strlen(s) + 1;
	while (i > 0)
	{
		if (ptr[i - 1] == c)
			return (ptr + (i - 1));
		i--;
	}
	return (NULL);
}
