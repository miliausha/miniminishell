#include "minishell.h"

void	child_process(t_all *all, int i)
{
	dup2(all->fd_in, 0);
	if (all->parts[i + 1] != NULL)
		dup2(all->pipefd[1], 1);
	close(all->pipefd[0]);
	start_parsing(all, all->parts[i]);
	// printf("before commands errno = %d\n", errno);
	run_commands(all);
	// printf("errno = %d\n", errno);
	// printf("g_exit = %d\n", g_exit);
	exit(g_exit);
}

void	run_pipe(t_all *all)
{
	int		i;
	int		status;
	// int		ret;
	pid_t	pid;

	i = -1;
	status = 0;
	// ret = EXIT_SUCCESS;
	all->fd_in = 0;
	while (all->parts[++i])
	{
		if (pipe(all->pipefd) < 0)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			child_process(all, i);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				g_exit = WEXITSTATUS(status);
				// printf("ret = %d, status = %d\n", ret, status);
				// g_exit = ret;
			}

			// sleep(1);
			// waitpid(0, &status, 0);
			// wait(0);
			// printf("status = %d\n", WIFEXITED(status));
			// if (!WIFEXITED(status))
				// printf("error = %d, errno = %d\n", WEXITSTATUS(status), errno);
			close(all->pipefd[1]);
			// if (status > 0)
			// 	g_exit = 1;
			// g_exit = status;
			// printf("status = %d\n", status);
			all->fd_in = all->pipefd[0];
		}
	}
}
