/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:27:02 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/02 19:27:03 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	i = 0;
	if (n)
	{
		n--;
		while (src[i] && n)
		{
			dest[i] = src[i];
			n--;
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
