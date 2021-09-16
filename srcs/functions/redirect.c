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

int	check_double_redirect(char *line, int *i)
{
	int	n;

	n = *i;
	if  (line[*i] && line[*i + 1])
	{
		skip_whitespace(line, &n);
		if (line[n] == '<' && line[n + 1] == '<')
			return(1);
	}
	return (0);
}

void	heredoc(t_all *all, int *fd, char *str, int *i)
{
	char	*line;
	char	*tmp;

	tmp = ft_calloc(sizeof(char), 1);
	line = ft_calloc(sizeof(char), 1);
	if (all->g_r != 1)
	{
		dup2(all->fd_0, 0);
		dup2(all->fd_1, 1);
	}
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
	if (!check_double_redirect(str, i))
	{
		*fd = open("heredoc.tmp", O_RDONLY);
		if (all->words)
			dup2(*fd, 0);
	}
	unlink("heredoc.tmp");
}

void	wrong_fd(t_all *all, char *line, int *i, int *fd)
{
	int fd_1;
	char	*tmp_redir;

	tmp_redir = ft_strdup(all->redir_file);
	free(all->redir_file);
	all->redir_file = NULL;
	while (line[*i])
	{
		if (line[*i] == '<' && line[*i + 1] == '<')
		{
			*i += 2;
			skip_whitespace(line, i);
			while (line[*i] && line[*i] != ' ' && !ft_strchr("<>", line[*i]))
			{
				add_arg(all, line[*i]);
				(*i)++;
			}
			all->redir_file = ft_strdup(all->arg);
			free(all->arg);
			all->arg = NULL;
			fd_1 = open("heredoc.tmp", O_WRONLY | O_CREAT | O_APPEND, 0666);
			heredoc(all, &fd_1, line, i);
		}
		(*i)++;
	}
	all->redir_file = ft_strdup(tmp_redir);
	free(tmp_redir);
	*fd = open_file(all);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(all->redir_file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	all->flag_redir = 0;
	all->redir = 1;
	if (all->words)
	{
		free_arr((void **)all->words);
		all->words = NULL;
	}
	if (all->redir_file)
	{		
		free(all->redir_file);
		all->redir_file = NULL;
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
		if (all->words && !all->flag_fd)
		{
			all->g_r = 1;
			dup2(fd, 1);
		}
	if (all->flag_redir == 3)
		if (all->words && !all->flag_fd)
			dup2(fd, 0);
	if (all->flag_redir == 4)
		heredoc(all, &fd, line, i);
	g_exit = 0;
	if (all->flag_fd == 2)
		g_exit = 1;
	all->redir = 1;
	all->flag_redir = 0;
	close(fd);
}
