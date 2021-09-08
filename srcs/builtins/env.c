#include "minishell.h"

void	sort_env(char **env_sorted)
{
	char	*tmp;
	int		i;

	i = -1;
	while (env_sorted[++i])
	{
		if (env_sorted[i + 1] && \
			ft_strncmp(env_sorted[i], env_sorted[i + 1], \
			ft_strlen(env_sorted[i])) > 0)
		{
			tmp = ft_strdup(env_sorted[i]);
			free(env_sorted[i]);
			env_sorted[i] = ft_strdup(env_sorted[i + 1]);
			free(env_sorted[i + 1]);
			env_sorted[i + 1] = ft_strdup(tmp);
			free(tmp);
			i = 0;
		}
	}
}

void	print_env(t_all *all)
{
	int	i;

	i = -1;
	while (all->env[++i])
	{
		if (!ft_strchr(all->env[i], '='))
			continue ;
		else
			ft_putendl_fd(all->env[i], 1);
	}
	g_exit = 0;
}
