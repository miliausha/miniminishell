#include "minishell.h"

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

void	heredoc(t_all *all, int *fd)
{
	char	*line;
	char	*tmp;

	tmp = ft_calloc(sizeof(char), 1);
	while (ft_strncmp(all->redir_file, line, \
		ft_strlen(all->redir_file) + 1))
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(all->redir_file, line, \
			ft_strlen(all->redir_file) + 1))
		{
			tmp = ft_strjoin(tmp, ft_strdup("\n"));
			tmp = ft_strjoin(tmp, ft_strdup(line));
		}
		free(line);
	}
	ft_putstr_fd(tmp + 1, *fd);
	ft_putchar_fd('\n', *fd);
	close(*fd);
	free(tmp);
	*fd = open("heredoc.tmp", O_RDONLY);
	if (all->words)
		dup2(*fd, 0);
}

void	wrong_fd(t_all *all, char *line, int *i, int *fd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(all->redir_file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	while (line[*i])
		(*i)++;
	all->flag_redir = 0;
	all->redir = 0;
	if (all->words)
	{
		free_arr((void **)all->words);
		all->words = NULL;
	}
	close(*fd);
	g_exit = 1;
}

void	redirect(t_all *all, char *line, int *i)
{
	int		fd;

	fd = open_file(all);
	if (fd == -1)
	{
		wrong_fd(all, line, i, &fd);
		return ;
	}
	if (all->flag_redir == 1 || all->flag_redir == 2)
		if (all->words)
			dup2(fd, 1);
	if (all->flag_redir == 3)
		if (all->words)
			dup2(fd, 0);
	if (all->flag_redir == 4)
		heredoc(all, &fd);
	g_exit = 0;
	all->flag_redir = 0;
	all->redir = 1;
	close(fd);
	unlink("heredoc.tmp");
}
