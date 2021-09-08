#include "minishell.h"

void	redirect_parser(char *line, t_all *all, int *i)
{
	all->flag_redir = 0;
	if (line[*i - 1] != ' ' && line[*i - 1])
		add_words(all);
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
}
