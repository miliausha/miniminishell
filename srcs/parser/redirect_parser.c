#include "minishell.h"

void 	get_filename(t_all *all, char *line, int *i)
{
	while (line[*i] && !ft_strchr("<>", line[*i]) && line[*i] != ' ')
	{
		add_arg(all, line[*i]);
		(*i)++;
	}
	if (all->redir_file)
		free(all->redir_file);
	all->redir_file = ft_strdup(all->arg);
	free(all->arg);
	all->arg = NULL;
	redirect(all, line, i);
	skip_whitespace(line, i);
}

int	check_if_digit(t_all *all)
{
	int	j;

	j = -1;
	while (all->arg[++j])
		if (!ft_isdigit(all->arg[j]))
			return (0);
	all->flag_fd = 1;
	if (ft_atoi(all->arg) > 2559)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(all->arg, 2);
		ft_putendl_fd(": Bad file descriptor", 2);
		if (all->words)
		{
			free_arr((void **)all->words);
			all->words = NULL;
		}
		all->flag_fd = 2;
		g_exit = 1;
	}
	free(all->arg);
	all->arg = NULL;
	return (1);
}

void	redirect_parser(char *line, t_all *all, int *i)
{
	all->flag_redir = 0;
	if (*i > 0 && all->arg && line[*i - 1] != ' ' && line[*i - 1])
	{
		if (!check_if_digit(all))
			add_words(all);
	}
	if (line[*i] == '>' && line[(*i) + 1] == '>')
	{
		all->flag_redir = 2;
		(*i)++;
	}
	else if (line[*i] == '>')
		all->flag_redir = 1;
	if (line[*i] == '<' && line[(*i) + 1] == '<')
	{
		all->flag_redir = 4;
		(*i)++;
	}
	else if (line[*i] == '<')
		all->flag_redir = 3;
	(*i)++;
	skip_whitespace(line, i);
	get_filename(all, line, i);
}
