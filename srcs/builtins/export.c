#include "minishell.h"

char	*cut_plus(char *words)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (words[i] != '+')
		i++;
	tmp = ft_calloc(sizeof(char), i + 1);
	if (!tmp)
		return (NULL);
	j = 0;
	while (j < i)
	{
		tmp[j] = words[j];
		j++;
	}
	tmp = ft_strjoin(tmp, ft_strdup(ft_strchr(words, '=')));
	return (tmp);
}

void	join_arg(t_all *all, char *words)
{
	char	**tmp;
	int		len;

	if (!check_match(all, words))
	{
		len = ft_strlen_arr(all->env) + 1;
		tmp = ft_calloc(sizeof(char *), len + 2);
		len = 0;
		while (all->env[len])
		{
			tmp[len] = ft_strdup(all->env[len]);
			len++;
		}
		if (ft_strchr(words, '+') && (ft_strchr(words, '+') + 1)
			== ft_strchr(words, '='))
			tmp[len] = cut_plus(words);
		else
			tmp[len] = ft_strdup(words);
		free_arr((void **)all->env);
		all->env = env_copy(tmp);
		free_arr((void **)tmp);
	}
	g_exit = 0;
}

void	print_env_with_scopes(t_all *all)
{
	int		i;
	char	**env_sorted;

	i = -1;
	env_sorted = env_copy_with_quotes(all->env);
	sort_env(env_sorted);
	while (env_sorted[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env_sorted[i], 1);
		free(env_sorted[i]);
	}
	free(env_sorted);
	g_exit = 0;
}

int	check_words(char *words)
{
	int	j;

	j = 1;
	if (!ft_isalpha(words[0]) && words[0] != '_')
	{
		error("minishell: export: `", words, "': not a valid identifier");
		g_exit = 1;
		return (0);
	}
	j = 1;
	while (j < (int)ft_strlen(words) && words[j] != '=')
	{
		if ((!ft_isalpha(words[j]) && \
			!ft_isdigit(words[j]) && words[j] != '_' && words[j] != '+') || \
			(words[j] == '+' && (words[j + 1] == '+' || words[j + 1] != '=')))
		{
			error("minishell: export: `", words, \
				"': not a valid identifier");
			g_exit = 1;
			return (0);
		}
		j++;
	}
	return (1);
}

void	print_export(t_all *all)
{
	int		i;

	i = 0;
	if (!all->words[1])
		print_env_with_scopes(all);
	else
	{
		while (all->words[++i])
		{
			if (!check_words(all->words[i]))
				continue ;
			else
				join_arg(all, all->words[i]);
		}
	}
}
