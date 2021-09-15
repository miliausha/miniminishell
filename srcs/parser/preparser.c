#include "minishell.h"

/*
**	static int	unspec_special_chars(char *line)
**		search for unspecified special characters like <\> or <;> 
**		in the line
**	algo:
**		check each symbol of line to unspecified special characters
**		ignore that chars between quots
**		also check for unclosed quots:
**			set q_flag if quots appear
**			if line end of line reached and q_flag not 0
**			there is unclosed quot in the line
**	return:
**		if there is unspecified special characters or\
**		unclosed quots then return (1)
**		else return (0)
*/

static int	check_spec_symbols(char *line, int *i)
{
	int	j;

	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
		(*i)++;
	j = *i;
	(*i)++;
	skip_whitespace(line, i);
	if (!line[*i])
	{
		error("minishell: syntax error near unexpected token `", \
			&line[*i - 1], "'");
		g_exit = 258;
		*i = j;
		return (1);
	}
	if (ft_strchr("<>|", line[*i]))
	{
		g_exit = 258;
		error("minishell: syntax error near unexpected token `", \
			&line[*i], "'");
		*i = j;
		return (1);
	}
	(*i) = j;
	return (0);
}

static int	checking_cicle(char	*line, int *i, int q_flag)
{
	if (line[*i] == '\\' || line[*i] == ';')
	{
		g_exit = 258;
		printf("Error! Unspecified special chars in line!\n");
		return (1);
	}
	if (ft_strchr("()&`", line[*i]))
	{
		g_exit = 258;
		printf("minishell: : syntax error near unexpected token `%c'\n", \
			line[*i]);
		return (1);
	}
	if (ft_strchr("<>|", line[*i]) && !q_flag)
	{
		if (check_spec_symbols(line, i))
			return (1);
	}
	return (0);
}

static int	unspec_special_chars(char *line)
{
	int	i;
	int	q_flag;

	i = 0;
	q_flag = 0;
	while (line[i])
	{
		q_flag = is_quot(line[i], q_flag);
		if (!q_flag)
		{
			if (checking_cicle(line, &i, q_flag))
				return (1);
		}
		i++;
	}
	if (q_flag)
	{
		g_exit = 258;
		printf("Error! Unclosed quotation marks!\n");
		return (1);
	}
	return (0);
}

int	preparser(char *line)
{
	if (unspec_special_chars(line))
		return (1);
	if (line && line[0] == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'",
			2);
		g_exit = 258;
		return (1);
	}
	return (0);
}
