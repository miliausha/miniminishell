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
		return (1);
	}
	while (j < (int)ft_strlen(words) && words[j])
	{
		if (!ft_isalpha(words[j]) && \
			!ft_isdigit(words[j]) && words[j] != '_')
		{
			error("minishell: unset: `", words, \
				"': not a valid identifier");
			g_exit = 1;
			return (1);
		}
		j++;
	}
	return (0);
}

char	**create_new_array(t_all *all, int i, char **tmp)
{
	int	j;
	int	k;
	int	len;

	j = -1;
	len = 0;
	k = 0;
	while (all->env[++j])
	{
		len = 0;
		while (all->env[j][len] != '=')
			len++;
		if (!ft_strncmp(all->env[j], all->words[i], len) && \
			!ft_strncmp(all->env[j], all->words[i], ft_strlen(all->words[i])))
			continue ;
		else
		{
			tmp[k] = ft_strdup(all->env[j]);
			k++;
		}
	}
	return (tmp);
}

void	delete_arg(t_all *all)
{
	int		i;
	char	**tmp;
	int		len;

	i = 0;
	while (all->words[++i])
	{
		if (check_match_unset(all, all->words[i]))
		{
			len = ft_strlen_arr(all->env) - 1;
			tmp = (char **)malloc(sizeof(char *) * len + 1);
			if (!tmp)
				return ;
			tmp[len] = NULL;
			tmp = create_new_array(all, i, tmp);
			free_arr((void **)all->env);
			all->env = env_copy(tmp);
			free_arr((void **)tmp);
		}
	}
	g_exit = 0;
}

void	ft_unset(t_all *all)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	if (!all->words[1])
		return ;
	while (all->words[++i])
		check += check_words_unset(all->words[i]);
	if (check)
		return ;
	delete_arg(all);
}
