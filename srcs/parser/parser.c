#include "minishell.h"

static void	init_parser(t_all *all, char *line)
{
	all->pipe_flag = 0;
	all->redir = 0;
	all->f_r = 0;
	all->flag_fd = 0;
	all->redir_file = NULL;
	all->parts = minishell_split(line, '|');
	all->pipe_count = ft_strlen_arr(all->parts) - 1;
}

void	builtins(t_all *all)
{
	int	len;

	len = ft_strlen(all->words[0]);
	if (!ft_strncmp(all->words[0], "echo", len) && len == 4)
		print_echo(all);
	else if (!ft_strncmp(all->words[0], "cd", len) && len == 2)
		print_cd(all);
	else if (!ft_strncmp(all->words[0], "pwd", len) && len == 3)
		get_pwd();
	else if (!ft_strncmp(all->words[0], "export", len) && len == 6)
		print_export(all);
	else if (!ft_strncmp(all->words[0], "exit", len) && len == 4)
		ft_exit(all);
	else if (!ft_strncmp(all->words[0], "unset", len) && len == 5)
		ft_unset(all);
	else if (!ft_strncmp(all->words[0], "env", len) && len == 3)
		print_env(all);
	else
	{
		if (!is_file_dir_exists(all))
			execve_cmd(all);
	}
}

void	run_commands(t_all *all)
{
	if (!all->words)
	{
		all->flag_fd = 0;
		dup2(all->fd_0, 0);
		dup2(all->fd_1, 1);
		return ;
	}
	if (all->flag_fd != 2)
		builtins(all);
	if (all->redir && !all->pipe_flag)
	{
		dup2(all->fd_0, 0);
		dup2(all->fd_1, 1);
		all->redir = 0;
	}
	if (all->words)
	{
		free_arr((void **)all->words);
		all->words = NULL;
	}
	all->flag_fd = 0;
	all->f_r = 0;
}

int	start_parsing(t_all *all, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quote_parser(line, all, &i, line[i]);
		else if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ' \
			&& line[i + 1] != '\"')
			env_parser(line, all, &i);
		else if (ft_strchr("<>", line[i]))
			redirect_parser(line, all, &i);
		else if (line[i] == ' ')
			check_redirect(all, line, &i);
		else if (line[i] != '\\')
			add_arg(all, line[i++]);
		else if (line[i] == '\\' && line[i + 1])
		{
			add_arg(all, line[i + 1]);
			i += 2;
		}
	}
	check_redirect(all, line, &i);
	return (0);
}

void	parser(t_all *all, char *line)
{
	init_parser(all, line);
	if (ft_strlen_arr(all->parts) > 500)
	{
		g_exit = 128;
		ft_putendl_fd("fork: Resource temporarily unavailable", 2);
		exit(g_exit);
	}
	else if (ft_strlen_arr(all->parts) > 1)
		all->pipe_flag = 1;
	if (all->parts)
	{
		if (all->pipe_flag)
			run_pipe(all);
		else
		{
			start_parsing(all, all->parts[0]);
			run_commands(all);
		}
	}
	free_arr((void **)all->parts);
	all->parts = NULL;
}
