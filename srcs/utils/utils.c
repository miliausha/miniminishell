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

int	is_file_dir_exists(t_all *all)
{
	int	status;

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

int	open_file(t_all *all)
{
	int	fd;

	if (all->flag_redir == 1)
		fd = open(all->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (all->flag_redir == 2)
		fd = open(all->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (all->flag_redir == 3)
		fd = open(all->redir_file, O_RDONLY);
	if (all->flag_redir == 4)
		fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_APPEND, 0666);
	return (fd);
}
