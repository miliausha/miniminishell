/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:43:01 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/09 14:44:46 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t len)
{
	unsigned char	*destptr;
	unsigned char	*srcptr;
	size_t			i;

	destptr = (unsigned char *)dest;
	srcptr = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		destptr[i] = srcptr[i];
		if (srcptr[i] == (unsigned char)c)
			return (destptr + i + 1);
		i++;
	}
	return (NULL);
}
