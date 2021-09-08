#include "minishell.h"

/*
**  int	is_quot(char c, int	q_flag)
**		for symbol ' - return == 1
**		for symbol " - return == 2
**		when q_flag == 1 (or 2), it means that quot was opened earlier
*/

int	is_quot(char c, int q_flag)
{
	if (c == '\'' && q_flag == 1)
		return (0);
	else if (c == '"' && q_flag == 2)
		return (0);
	else if (c == '\'' && q_flag != 2)
		return (1);
	else if (c == '"' && q_flag != 1)
		return (2);
	return (q_flag);
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while ((s[i] == 32 || s[i] == '\t') && s[i])
		i++;
	return (i);
}

void	add_arg(t_all *all, char c)
{
	char	*str;
	int		i;

	i = -1;
	if (!all->arg)
		all->arg = ft_calloc(sizeof(char), 1);
	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	all->arg = ft_strjoin(all->arg, str);
}

void	add_words(t_all *all)
{
	char	**arr;
	int		len;
	int		i;

	i = -1;
	if (!all->words)
		all->words = ft_calloc(sizeof(char *), 1);
	len = ft_strlen_arr(all->words) + 1;
	arr = (char **)malloc(sizeof(char *) * len + 1);
	if (!arr)
		return ;
	arr[len] = NULL;
	while (all->words[++i])
	{
		arr[i] = ft_strdup(all->words[i]);
		free(all->words[i]);
	}
	arr[i] = ft_strdup(all->arg);
	free(all->words);
	free(all->arg);
	all->arg = NULL;
	all->words = arr;
}
