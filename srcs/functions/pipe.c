#include "minishell.h"

void	child_process(t_all *all, int status, int i)
{
	dup2(all->fd_in, 0);
	if (all->parts[i + 1] != NULL)
		dup2(all->pipefd[1], 1);
	close(all->pipefd[0]);
	start_parsing(all, all->parts[i]);
	run_commands(all);
	exit(status);
}

void	run_pipe(t_all *all)
{
	int		i;
	int		status;
	pid_t	pid;

	i = -1;
	status = 0;
	all->fd_in = 0;
	while (all->parts[++i])
	{
		if (pipe(all->pipefd) < 0)
			exit(0);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			child_process(all, status, i);
		else
		{
			wait(&status);
			close(all->pipefd[1]);
			if (status > 0)
				g_exit = 1;
			all->fd_in = all->pipefd[0];
		}
	}
}
