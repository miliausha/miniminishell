#include "minishell.h"

void	free_arr(void **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_at_exit(t_all *all)
{
	if (all->words)
		free_arr((void **)all->words);
	if (all->env)
		free_arr((void **)all->env);
}
