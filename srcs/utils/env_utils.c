#include "minishell.h"

int	env_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (i + 1);
		i++;
	}
	return (i + 1);
}

char	*env_path_search(char **env, char *str)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			path = ft_strtrim(env[i], str);
	}
	if (!path)
		return (NULL);
	return (path);
}

void	update_env(t_all *all, char *str, char *pwd)
{
	int		i;
	int		len;
	char	**tmp;
	char	*tmp1;

	i = -1;
	tmp = ft_calloc(sizeof(char *), ft_strlen_arr(all->env) + 1);
	if (!tmp)
		exit (EXIT_FAILURE);
	while (all->env[++i])
	{
		len = env_len(all->env[i]) - 1;
		if (!ft_strncmp(all->env[i], str, ft_strlen(str)) && \
			!ft_strncmp(all->env[i], str, len))
		{	
			tmp1 = ft_strjoin(ft_strdup(str), ft_strdup("="));
			tmp[i] = ft_strjoin(tmp1, ft_strdup(pwd));
		}
		else
			tmp[i] = ft_strdup(all->env[i]);
	}
	free_arr((void **)all->env);
	all->env = env_copy(tmp);
	free_arr((void **)tmp);
}

char	**dup_env(char **env)
{
	char	**ret;
	int		i;

	i = 0;
	while (env[i])
		i++;
	ret = (char **)malloc((sizeof(char *) + 2) * i);
	if (!ret)
		return (NULL);
	ret[i + 1] = NULL;
	ret[i] = ft_strdup("OLDPWD");
	while (i--)
		ret[i] = ft_strdup(env[i]);
	return (ret);
}

char	**env_copy(char **env)
{
	int		i;
	int		len;
	char	**env_copy;

	i = 0;
	len = ft_strlen_arr(env);
	env_copy = (char **)malloc(sizeof(char *) * len + 1);
	if (!env_copy)
		return (NULL);
	env_copy[len] = NULL;
	i = -1;
	while (env[++i])
		env_copy[i] = ft_strdup(env[i]);
	return (env_copy);
}
