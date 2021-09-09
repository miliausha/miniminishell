#include "minishell.h"

int	check_match_unset(t_all *all, char *words)
{
	int	i;
	int	len;

	i = 0;
	while (all->env[i])
	{
		len = 0;
		while (all->env[i][len] != '=')
			len++;
		if (!ft_strncmp(all->env[i], words, len) && \
			!ft_strncmp(all->env[i], words, (int)ft_strlen(words)))
			return (1);
		i++;
	}
	return (0);
}

int	check_words_unset(char *words)
{
	int	j;

	j = 1;
	if (!ft_isalpha(words[0]) && words[0] != '_')
	{
		error("minishell: unset: `", words, "': not a valid identifier");
		g_exit = 1;
		return (0);
	}
	while (j < (int)ft_strlen(words) && words[j])
	{
		if (!ft_isalpha(words[j]) && \
			!ft_isdigit(words[j]) && words[j] != '_')
		{
			error("minishell: unset: `", words, \
				"': not a valid identifier");
			g_exit = 1;
			return (0);
		}
		j++;
	}
	return (1);
}

char	**create_new_array(t_all *all, char **tmp, char *words)
{
	int	j;
	int	i;
	int	len;

	j = -1;
	len = 0;
	i = 0;
	while (all->env[++j])
	{
		len = 0;
		while (all->env[j][len] != '=')
			len++;
		if (!ft_strncmp(all->env[j], words, len) && \
			!ft_strncmp(all->env[j], words, ft_strlen(words)))
			continue ;
		else
		{
			tmp[i] = ft_strdup(all->env[j]);
			i++;
		}
	}
	return (tmp);
}

void	delete_arg(t_all *all, char *words)
{
	char	**tmp;
	int		len;

	if (check_match_unset(all, words))
	{
		len = ft_strlen_arr(all->env) - 1;
		tmp = (char **)malloc(sizeof(char *) * len + 2);
		if (!tmp)
			return ;
		tmp[len] = NULL;
		tmp = create_new_array(all, tmp, words);
		free_arr((void **)all->env);
		all->env = env_copy(tmp);
		free_arr((void **)tmp);
	}
	g_exit = 0;
}

void	ft_unset(t_all *all)
{
	int	i;

	i = 0;
	if (!all->words[1])
		return ;
	while (all->words[++i])
	{
		if (!check_words_unset(all->words[i]))
			continue ;
		else
			delete_arg(all, all->words[i]);
	}
}
