#include "minishell.h"

/*
**	int	count_parts(char *line, char c)
**	decription:
**		count the number of parts into which we split string
**	variables:
**		- q_flag - flag that will change when quots appear;
**		- parts - number of parts;
**		- i - counter;
**	algo:
**		1) if line not empty incr. "parts" (parts++);
**		2) skip all spaces
**		3) check all symbols of line
**			3.1) set "q_flag" (description in "utils.c" file)
**			3.2) if delimeter char occurs incr. "parts"
**				(consider double delimeter chars, symbols between quots, 
**				'\' symbol);
**		4) return "parts"
*/

static int	count_parts(char *line, char c)
{
	int	q_flag;
	int	parts;
	int	i;

	q_flag = 0;
	parts = 0;
	i = 0;
	if (line && line[i])
	{
		parts++;
		while (line[i] == ' ' || line[i] == '\t' || line[i] == c)
			i++;
		while (line[i])
		{
			q_flag = is_quot(line[i], q_flag);
			if (!q_flag && line[i] != c && line[i + 1] == c && line[i + 2])
				parts++;
			i++;
		}
	}
	return (parts);
}

/*
** not ended
*/

void	fill_parts(char **arr, char *line, char c, int n)
{
	int	counter;
	int	start;
	int	end;
	int	q_flag;

	counter = 0;
	start = 0;
	end = 0;
	q_flag = 0;
	while (counter < n)
	{
		q_flag = is_quot(line[end], q_flag);
		if ((!q_flag && line[end] && line[end] != c && line[end + 1] == c)
			|| (!line[end] && end > start))
		{
			arr[counter++] = ft_substr(line, start, end - start + 1);
			end += skip_spaces(line + end + 2);
			start = end + 2;
		}
		end++;
	}
}

/*
**	divide "line" variable to the parts by delimeter (char c)
**	variables:
**		- new - array of strings (where we put return);
**		- elems - number of parts;
**	algo:
**		1) count how many parts need to return (put result to "elems");
**		2) malloc "new"
**		3) fill "new"
*/

char	**minishell_split(char *line, char c)
{
	char	**new;
	int		elems;

	new = NULL;
	if (line && line[0])
	{
		elems = count_parts(line, c);
		new = (char **)malloc(sizeof(char *) * elems + 1);
		new[elems] = NULL;
		fill_parts(new, line, c, elems);
	}
	return (new);
}
