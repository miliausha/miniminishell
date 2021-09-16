#include "minishell.h"

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
	all->g_r = 0;
	// printf("g_exit run_commands = %d\n", g_exit);
}

void	check_redirect(t_all *all, char *line, int *i)
{
	if (all->arg)
	{
		if (!all->flag_redir)
			add_words(all);
		else
		{
			if (all->redir_file)
			{
				free(all->redir_file);
				all->redir_file = NULL;
			}
			all->redir_file = ft_strdup(all->arg);
			free(all->arg);
			all->arg = NULL;
			redirect(all, line, i);
			free(all->redir_file);
			all->redir_file = NULL;
		}
	}
	skip_whitespace(line, i);
}

int	start_parsing(t_all *all, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		// ft_putstr_fd("line [i] = |", 2);
		// ft_putchar_fd(line[i], 2);
		// ft_putstr_fd("|\t", 2);
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_parser(line, all, &i, line[i]);
			// printf("quote parser\n");
		}
		else if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ' \
			&& line[i + 1] != '\"')
		{
			env_parser(line, all, &i);
			// printf("env parser\n");
		}
		else if (ft_strchr("<>", line[i]))
		{

			redirect_parser(line, all, &i);
			// printf("redir parser\n");
		}
		else if (line[i] == ' ')
		{
			check_redirect(all, line, &i);
			// printf("check redir\n");
		}
		else if (line[i] != '\\')
		{
			add_arg(all, line[i++]);
			// printf("add arg\n");
		}
		else if (line[i] == '\\' && line[i + 1])
		{
			add_arg(all, line[i + 1]);
			i += 2;
			// printf("add arg2\n");
		}
	}
	check_redirect(all, line, &i);
	// if (all->arg)
	// {
	// 	free(all->arg);
	// 	all->arg = NULL;
	// }
	return (0);
}

void	parser(t_all *all, char *line)
{
	all->pipe_flag = 0;
	all->redir = 0;
	all->g_r = 0;
	all->flag_fd = 0;
	all->redir_file = NULL;
	all->parts = minishell_split(line, '|');
	all->pipe_count = ft_strlen_arr(all->parts) - 1;
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
	// printf("g_exit parser = %d\n", g_exit);

}
