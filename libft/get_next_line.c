#include "libft.h"

static int	str_from_tail(char **tail, char **line, char **is_n)
{
	*is_n = NULL;
	if (*tail)
	{
		*is_n = ft_strchr(*tail, '\n');
		if (*is_n)
		{
			**is_n = '\0';
			*line = ft_strdup(*tail);
			ft_strcpy(*tail, ++(*is_n));
		}
		else
		{
			*line = ft_strdup(*tail);
			free(*tail);
			*tail = NULL;
		}
	}
	else
	{
		*line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*line))
			return (1);
		*line[0] = '\0';
	}
	return (0);
}

static int	write_to_line(char **line, char *buf, char **tail, char **is_n)
{
	*is_n = ft_strchr(buf, '\n');
	if (*is_n)
	{
		**is_n = '\0';
		*tail = ft_strdup(++(*is_n));
		if (!*tail)
			return (-1);
	}
	*line = ft_strjoin(*line, buf);
	if (!*line)
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	int			ret;
	char		*is_n;
	static char	*tail;

	ret = read(fd, 0, 0);
	if (!line || BUFFER_SIZE <= 0 || ret < 0)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (str_from_tail(&tail, line, &is_n) && !buf && !*line)
		return (-1);
	if (!is_n)
		ret = read(fd, buf, BUFFER_SIZE);
	while (!is_n && ret)
	{
		buf[ret] = '\0';
		if (write_to_line(line, buf, &tail, &is_n))
			return (-1);
		if (!is_n)
			ret = read(fd, buf, BUFFER_SIZE);
	}
	if (is_n)
		return (1);
	return (0);
}
