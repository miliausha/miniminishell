/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:43:34 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/09 14:42:09 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	char	*destptr;
	char	*srcptr;

	if (!dest && !src)
		return (NULL);
	destptr = (char *)dest;
	srcptr = (char *)src;
	while (len--)
		*destptr++ = *srcptr++;
	return (dest);
}
