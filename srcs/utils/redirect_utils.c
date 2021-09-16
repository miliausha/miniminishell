#include "minishell.h"

int	check_double_redirect(char *line, int *i)
{
	int	n;

	n = *i;
	if (line[*i] && line[*i + 1])
	{
		skip_whitespace(line, &n);
		if (line[n] == '<' && line[n + 1] == '<')
			return (1);
	}
	return (0);
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
