#include "minishell.h"

void	add_tmp(char **tmp, char c)
{
	char	*str;
	int		i;

	i = -1;
	if (!(*tmp))
		*tmp = ft_calloc(sizeof(char), 1);
	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	*tmp = ft_strjoin((*tmp), str);
}

char	*get_result(t_all *all, char *res, char **tmp)
{
	if (!ft_strncmp(*tmp, "?", 1))
		res = ft_itoa(g_exit);
	else
		res = env_path_search(all->env, *tmp);
	free(*tmp);
	if (!res && all->words)
		res = ft_strdup(" ");
	if (!res && !all->words)
		return (NULL);
	return (res);
}

void	get_argument(t_all *all, char **res, char **tmp)
{
	if (!all->arg)
		all->arg = ft_calloc(sizeof(char), 1);
	*tmp = ft_strjoin(all->arg, *res);
	all->arg = ft_strdup(*tmp);
	free(*tmp);
}

void	env_parser(char *line, t_all *all, int *i)
{
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	(*i)++;
	if (ft_isdigit(line[*i]))
		add_tmp(&tmp, line[(*i)++]);
	else if (line[*i] == '?')
	{
		add_tmp(&tmp, line[*i]);
		(*i)++;
	}
	else if (!ft_isdigit(line[*i]))
	{
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			add_tmp(&tmp, line[(*i)++]);
		add_tmp(&tmp, '=');
	}
	res = get_result(all, res, &tmp);
	if (!res)
		return ;
	get_argument(all, &res, &tmp);
}
