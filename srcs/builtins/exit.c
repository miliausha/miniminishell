#include "minishell.h"

void	check_exit_arg(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			error("minishell: exit: ", str, ": numeric argument required");
			exit(255);
		}
		i++;
	}
}

void	ft_exit(t_all *all)
{
	ft_putendl_fd("exit", 1);
	if (ft_strlen_arr(all->words) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments\n", 2);
		g_exit = 1;
		return ;
	}
	free_arr((void **)all->env);
	free_arr((void **)all->words);
	free_arr((void **)all->parts);
	if ((all->words && !all->words[1]) || !all->words)
		exit(g_exit);
	if (all->words)
	{
		check_exit_arg(all->words[1]);
		exit(ft_atoi(all->words[1]));
	}
}
