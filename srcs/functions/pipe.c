#include "minishell.h"

// void	child_process(t_all *all, int i)
// {
// 	dup2(all->fd_in, 0);
// 	if (all->parts[i + 1] != NULL)
// 		dup2(all->pipefd[1], 1);
// 	close(all->pipefd[0]);
// 	start_parsing(all, all->parts[i]);
// 	// printf("before commands errno = %d\n", errno);
// 	gettimeofday(&all->tv, NULL);
// 	printf("time1 = %ld\n", all->tv.tv_sec * 1000 + all->tv.tv_usec / 1000 - all->start);
// 	run_commands(all);
// 	// printf("errno = %d\n", errno);
// 	// printf("g_exit = %d\n", g_exit);
	
// 	exit(g_exit);
// 	// kill(getpid(), SIGKILL);

// }

// void	run_pipe(t_all *all)
// {
	
// 	//
// 	int		i;
// 	int		status;
// 	// int		ret;
// 	pid_t	pid;

// 	i = -1;
// 	status = 0;
// 	// ret = EXIT_SUCCESS;
// 	all->fd_in = 0;
// 	while (all->parts[++i])
// 	{
// 		if (pipe(all->pipefd) < 0)
// 			exit(EXIT_FAILURE);
// 		pid = fork();
// 		if (pid < 0)
// 			exit(EXIT_FAILURE);
// 		else if (pid == 0)
// 		{
// 			// gettimeofday(&all->tv, NULL);
// 			// printf("time2 = %ld\n", all->tv.tv_sec * 1000 + all->tv.tv_usec / 1000 - all->start);
// 			child_process(all, i);
// 		}
// 		else
// 		{
// 			// gettimeofday(&all->tv, NULL);
// 			// printf("time3 = %ld\n", all->tv.tv_sec * 1000 + all->tv.tv_usec / 1000 - all->start);
// 			// sleep(1);
// 			waitpid(pid, &status, 0);
// 			// gettimeofday(&all->tv, NULL);
// 			// printf("time4 = %ld\n", all->tv.tv_sec * 1000 + all->tv.tv_usec / 1000 - all->start);
// 			if (WIFEXITED(status))
// 			{
// 				g_exit = WEXITSTATUS(status);
// 				// sleep(5);
// 				// printf("g_exit = %d, status = %d\n", g_exit, status);
// 				// g_exit = ret;
// 			}

// 			// sleep(1);
// 			// waitpid(0, &status, 0);
// 			// wait(0);
// 			// printf("status = %d\n", WIFEXITED(status));
// 			// if (!WIFEXITED(status))
// 				// printf("error = %d, errno = %d\n", WEXITSTATUS(status), errno);
// 			close(all->pipefd[1]);
// 			// if (status > 0)
// 			// 	g_exit = 1;
// 			// g_exit = status;
// 			// printf("status = %d\n", status);
// 			all->fd_in = all->pipefd[0];
// 		}
// 	}
// }


void	child_process(t_all *all, int i)
{
	dup2(all->pipefd[1], 1);
	close(all->pipefd[0]);
	close(all->pipefd[1]);
	start_parsing(all, all->parts[i]);
	run_commands(all);
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
		if (all->parts[i + 1] == NULL)
			break;
		if (pipe(all->pipefd) < 0)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			child_process(all, i);
			kill(pid, SIGKILL);
		}
		else
		{
			dup2(all->pipefd[0], 0);
			close(all->pipefd[0]);
			close(all->pipefd[1]);
			if (WIFEXITED(status))
			{
				g_exit = WEXITSTATUS(status);
			}
		}
	}
	all->pipe_flag = 0;
	start_parsing(all, all->parts[i]);
	run_commands(all);
	while (all->pipe_count)
	{
		dup2(all->fd_0, 0);
		dup2(all->fd_1, 1);
		wait(&status);
		all->pipe_count--;
	}
}
