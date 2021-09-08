/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:43:58 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/02 14:44:16 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*destptr;
	char	*srcptr;

	if (!dest && !src)
		return (NULL);
	destptr = (char *)dest;
	srcptr = (char *)src;
	if (destptr < srcptr)
	{
		while (len)
		{
			*destptr++ = *srcptr++;
			len--;
		}
	}
	else
	{
		while (len)
		{
			*(destptr + (len - 1)) = *(srcptr + (len - 1));
			len--;
		}
	}
	return (dest);
}
