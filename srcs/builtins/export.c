#include "minishell.h"

void	join_arg(t_all *all)
{
	char	**tmp;
	int		i;
	int		len;

	i = 0;
	printf("check\n");
	while (all->words[++i])
	{
		if (!check_match(all, all->words[i]))
		{
			len = ft_strlen_arr(all->env) + 1;
			tmp = ft_calloc(sizeof(char *), len + 2);
			len = 0;
			while (all->env[len])
			{
				tmp[len] = ft_strdup(all->env[len]);
				len++;
			}
			tmp[len] = ft_strdup(all->words[i]);
			free_arr((void **)all->env);
			all->env = env_copy(tmp);
			free_arr((void **)tmp);
		}
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
		return (1);
	}
	j = 1;
	while (j < (int)ft_strlen(words) && words[j] != '=')
	{
		if (!ft_isalpha(words[j]) && \
			!ft_isdigit(words[j]) && words[j] != '_')
		{
			error("minishell: export: `", words, \
				"': not a valid identifier");
			g_exit = 1;
			return (1);
		}
		j++;
	}
	return (0);
}

void	print_export(t_all *all)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	if (!all->words[1])
		print_env_with_scopes(all);
	else
	{
		while (all->words[++i])
			count += check_words(all->words[i]);
		if (count)
			return ;
		join_arg(all);
	}
}
