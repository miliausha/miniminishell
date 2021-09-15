/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 23:53:48 by aezzara           #+#    #+#             */
/*   Updated: 2021/09/07 23:53:54 by aezzara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*
**	char	*get_cmd_path(char **env, char **arr)
**		find the path (by using function 'which') where
**		system functions are stored
*/

static char	*get_cmd_path(t_all *all, char **arr)
{
	int		p[2];
	pid_t	pid;
	char	*path;
	int		status;
	
	path = NULL;
	if (pipe(p) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		g_exit = execve("/usr/bin/which", arr, all->env);
		// if (g_exit < 0)
		exit(g_exit);
		// if (arr[0] && arr[1])
		// 	perror(arr[1]);
		// close(p[1]);
		// exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(p[1]);
		get_next_line(p[0], &path);
		close(p[0]);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);

	}
	return (path);
}

/*
**	char	**offset_arr(char **arr, char *str)
**		offser given arr (n - element become n + 1)
**		then fill first element with 'str'
**		(that func needed to use execve later)
*/

char	**offset_arr(char **arr, char *str)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	new_arr[i + 1] = NULL;
	while (i--)
		new_arr[i + 1] = ft_strdup(arr[i]);
	new_arr[0] = ft_strdup(str);
	return (new_arr);
}

int	ft_execve_func(char *path, t_all *all)
{
	pid_t	pid;
	int		status;
	// int		fd[2];

	// if (pipe(fd) < 0)
	// 	exit(EXIT_FAILURE);
	// printf("path = %s\n", path);
	// int i = 0;
	// while (all->words[i])
	// 	printf("words = %s\n", all->words[i++]);
	status = 0;
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		execve(path, all->words, all->env);
		if (all->words[0] && all->words[1])
			perror(all->words[1]);
		// close(fd[1]);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		// g_exit = status / 256;
		//printf("status = %d\n", status);
		// close(fd[1]);
		// close(fd[0]);
	}
	return (0);
}

void	execve_cmd(t_all *all)
{
	char	*cmd_path;
	char	**arr;

	set_signals(1);
	arr = offset_arr(all->words, "minishell");
	if (!arr)
		exit(EXIT_FAILURE);
	cmd_path = get_cmd_path(all, arr);
	if (!cmd_path || (cmd_path && !cmd_path[0]))
		cmd_not_found(all->words[0]);
	else if (all->pipe_flag == 0)
	{
		g_exit = 0;
		ft_execve_func(cmd_path, all);
	}
	else
	{
		g_exit = 0;
		execve(cmd_path, all->words, all->env);
		// printf("cmd path = %s, errno = %d\n", cmd_path, errno);
		g_exit = errno;
		exit(g_exit);
	}
	// printf("g_exit execve_cmd1 = %d\n", g_exit);
	set_signals(0);
	free_arr((void **)arr);
	free(cmd_path);
	// printf("g_exit execve_cmd2 = %d\n", g_exit);
}
