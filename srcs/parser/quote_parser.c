#include "minishell.h"

void	quote_parser(char *line, t_all *all, int *i, char c)
{
	(*i)++;
	all->flag_quot = 1;
	if (line[*i] == c)
		add_arg(all, 0);
	while (line[(*i)] && line[(*i)] != c)
	{
		if (c == '\"' && line[*i] == '\\' && \
			ft_strchr("$\\\"`", line[*i + 1]) && line[*i + 1])
		{
			(*i)++;
			add_arg(all, line[*i]);
			(*i)++;
		}
		if (c == '\"' && line[*i] == '$' && line[*i + 1] != '\"')
		{
			env_parser(line, all, i);
		}
		else
			add_arg(all, line[(*i)++]);
	}
	(*i)++;
	all->flag_quot = 0;
}
