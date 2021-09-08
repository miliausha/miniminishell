#include "minishell.h"

void	print_arg(char **words, int i, int n_flag)
{
	while (words[++i])
	{
		ft_putstr_fd(words[i], 1);
		if (words[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}

int	print_echo(t_all *all)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 0;
	if (!all->words[1])
	{
		ft_putchar_fd('\n', 1);
		g_exit = 0;
		return (0);
	}
	while (all->words[++i])
	{
		if (!ft_strncmp("-n", all->words[i], ft_strlen(all->words[i])) && \
			!ft_strncmp("-n", all->words[1], ft_strlen(all->words[1])))
			n_flag++;
	}
	i = n_flag;
	print_arg(all->words, i, n_flag);
	g_exit = 0;
	return (0);
}
