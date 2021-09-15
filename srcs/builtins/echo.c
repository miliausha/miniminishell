#include "minishell.h"

void	print_arg(char **words, int i, int n_flag)
{
	while (words[++i])
	{
		ft_putstr_fd(words[i], 1);
		// printf("word = |%s|\n", words[i]);
		if (words[i + 1] && words[i][0] && words[i + 1][0])
		{
			ft_putchar_fd(' ', 1);
			// printf("c = |%c|\n", words[i + 1][0]);
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}

void	check_n(t_all *all, int *n_flag)
{
	int	i;
	int	j;

	i = 0;
	while (all->words[++i])
	{
		j = 0;
		while (all->words[i][++j])
		{
			if (all->words[i][j] != 'n')
				return ;
		}
		(*n_flag)++;
	}
}

int	print_echo(t_all *all)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (!all->words[1])
	{
		ft_putchar_fd('\n', 1);
		g_exit = 0;
		return (0);
	}
	if (all->words[1][0] == '-' && all->words[1][1] == 'n')
		check_n(all, &n_flag);
	i = n_flag;
	print_arg(all->words, i, n_flag);
	g_exit = 0;
	return (0);
}
