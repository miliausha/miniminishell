/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:42:33 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/12 12:33:38 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*memory_free(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	ft_counter(char const *s, char c)
{
	int		i;
	int		counter;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static int	get_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static char	**get_str(char const *s, int match, char c, char **str)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < match)
	{
		while (*s == c)
			s++;
		len = get_len(s, c);
		str[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!str[i])
			return (memory_free(str, i));
		j = 0;
		while (j < len)
			str[i][j++] = *s++;
		str[i][j] = '\0';
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char	const *s, char c)
{
	char	**str;
	int		match;

	if (!s)
		return (NULL);
	match = ft_counter(s, c);
	str = (char **)malloc(sizeof(char *) * (match + 1));
	if (!str)
		return (NULL);
	str = get_str(s, match, c, str);
	return (str);
}
