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

int	is_file_dir_exists(t_all *all)
{
	int status;

	status = 0;
	all->s_stat.st_mode = 0;
	if (all->words && all->words[0])
	{
		status = stat(all->words[0], &all->s_stat);
		if (status == -1 && ft_strchr(all->words[0], '/'))
		{
			error("minishell: ", all->words[0],
				": No such file or directory");
			g_exit = 127;
			return (1);
		}
		if (status != -1 && (all->s_stat.st_mode & S_IFDIR) == S_IFDIR)
		{
			error("minishell: ", all->words[0], ": is a directory");
			g_exit = 126;
			return (1);
		}
	}
	else
		return (1);
	return (0);
}
