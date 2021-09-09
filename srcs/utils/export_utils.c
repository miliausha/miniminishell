#include "minishell.h"

char	*join_quotes(char *env)
{
	char	*env_copy;

	if (ft_strchr(env, '=') && ft_strchr(env, '=') + 1)
	{
		env_copy = ft_strtrim(env, ft_strchr(env, '=') + 1);
		if (env_copy[ft_strlen(env_copy) - 1] != '=')
			env_copy = ft_strjoin(env_copy, ft_strdup("="));
		env_copy = ft_strjoin(env_copy, ft_strdup("\""));
		env_copy = ft_strjoin(env_copy, ft_strdup(ft_strchr(env, '=') + 1));
		env_copy = ft_strjoin(env_copy, ft_strdup("\""));
	}
	else if (ft_strchr(env, '=') && !ft_strchr(env, '=') + 1)
	{
		env_copy = ft_strtrim(env, ft_strchr(env, '=') + 1);
		env_copy = ft_strjoin(env_copy, ft_strdup(""""));
	}
	else
		env_copy = ft_strdup(env);
	return (env_copy);
}

char	**env_copy_with_quotes(char **env)
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
		env_copy[i] = join_quotes(env[i]);
	return (env_copy);
}

char	*match_cicle(char *env, char *tmp, char *words, int *match)
{
	int		len;
	char	*copy;

	len = 0;
	copy = NULL;
	while (env[len] != '=')
		len++;
	if (!ft_strncmp(env, tmp, len) && !ft_strncmp(env, tmp, ft_strlen(tmp)))
	{
		if (!ft_strchr(words, '=') && ft_strchr(env, '='))
			copy = ft_strdup(env);
		else
			copy = ft_strdup(words);
		(*match)++;
	}
	else
		copy = ft_strdup(env);
	return (copy);
}

int	check_match(t_all *all, char *words)
{
	int		i;
	int		len;
	int		match;
	char	*tmp;
	char	**copy;

	i = -1;
	match = 0;
	len = ft_strlen_arr(all->env);
	copy = ft_calloc(sizeof(char *), len + 1);
	if (ft_strchr(words, '='))
		tmp = ft_strtrim(words, ft_strchr(words, '='));
	else
		tmp = ft_strdup(words);
	while (all->env[++i])
		copy[i] = match_cicle(all->env[i], tmp, words, &match);
	free_arr((void **)all->env);
	all->env = env_copy(copy);
	free_arr((void **)copy);
	free(tmp);
	return (match);
}
