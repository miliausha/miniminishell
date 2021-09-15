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

	// printf("res = |%s|, tmp = |%s|\n", res, *tmp);
	if (!res && all->words && !ft_isdigit(*tmp[0]))
		res = NULL;//ft_strdup("");
	free(*tmp);
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
	if (ft_isdigit(line[*i + 1]) || line[*i + 1] == '?')
		add_tmp(&tmp, line[(*i += 2) - 1]);
	else if (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_')
	{
		(*i)++;
		while (ft_isalnum(line[*i]) || line[(*i)] == '_')
			add_tmp(&tmp, line[(*i)++]);
		add_tmp(&tmp, '=');
	}
	else
	{
		add_arg(all, line[*i]);
		(*i)++;
	}
	if (tmp)
	{
		res = get_result(all, res, &tmp);
		if (!res)
			return ;
		get_argument(all, &res, &tmp);
	}
}
