/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:21:03 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/07 13:35:24 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		a;
	int		i;
	char	*arr;

	a = nmemb * size;
	arr = (char *)malloc(sizeof(char) * a);
	if (!arr)
		return (NULL);
	i = 0;
	while (a--)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}
