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
	if ((ft_strlen(str) == 19 && ft_strncmp(str, "9223372036854775807", 20) > 0) \
		|| (ft_strlen(str) == 20 && ft_strncmp(str, "-9223372036854775808", 21) > 0) \
		|| ft_strlen(str) > 20)
	{
		error("minishell: exit: ", str, ": numeric argument required");
		exit(255);
	}
}

void	ft_exit(t_all *all)
{
	// if ((all->words && !all->words[1]) || !all->words)
	if (!all->words)
		exit(g_exit);
	ft_putendl_fd("exit", 2);
	if (all->words && !all->words[1])
		exit(g_exit);
	if (all->words[1])
		check_exit_arg(all->words[1]);
	if (ft_strlen_arr(all->words) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_exit = 1;
		return ;
	}
	g_exit = ft_atoi(all->words[1]);
	exit(g_exit);
}
