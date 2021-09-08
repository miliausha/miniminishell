#include "minishell.h"

void	error(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
}

int	ft_strlen_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

void	cmd_not_found(char *s)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_exit = 127;
}
