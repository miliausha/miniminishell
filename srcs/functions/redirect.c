#include "minishell.h"

void	read_from_redirect(t_all *all, char **tmp)
{
	char	*line;

	line = ft_calloc(sizeof(char), 1);
	while (ft_strncmp(all->redir_file, line, \
		ft_strlen(all->redir_file) + 1))
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(all->redir_file, line, \
			ft_strlen(all->redir_file) + 1))
		{
			*tmp = ft_strjoin(*tmp, ft_strdup("\n"));
			*tmp = ft_strjoin(*tmp, ft_strdup(line));
		}
		free(line);
	}
}

void	heredoc(t_all *all, int *fd, char *str, int *i)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char), 1);
	if (all->f_r != 1)
	{
		dup2(all->fd_0, 0);
		dup2(all->fd_1, 1);
	}
	read_from_redirect(all, &tmp);
	ft_putstr_fd(tmp + 1, *fd);
	if (ft_strlen(tmp + 1) > 0)
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

void	heredoc_redirection(t_all *all, char *line, int *i)
{
	int	fd_1;

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
}

void	wrong_fd(t_all *all, char *line, int *i, int *fd)
{
	char	*tmp_redir;

	tmp_redir = ft_strdup(all->redir_file);
	free(all->redir_file);
	all->redir_file = NULL;
	heredoc_redirection(all, line, i);
	all->redir_file = ft_strdup(tmp_redir);
	free(tmp_redir);
	*fd = open_file(all);
	ft_putstr_fd("minishell: ", 2);
	error(all->redir_file, ": ", strerror(errno));
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
	if ((all->flag_redir == 1 || all->flag_redir == 2)
		&& all->words && !all->flag_fd)
	{
		all->f_r = 1;
		dup2(fd, 1);
	}
	if (all->flag_redir == 3 && all->words && !all->flag_fd)
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
