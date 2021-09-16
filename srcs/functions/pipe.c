#include "minishell.h"

void	child_process(t_all *all, int i)
{
	dup2(all->pipefd[1], 1);
	close(all->pipefd[0]);
	close(all->pipefd[1]);
	start_parsing(all, all->parts[i]);
	run_commands(all);
}

void	fork_pipe(t_all *all, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		child_process(all, i);
		kill(getpid(), SIGKILL);
	}
	else
	{
		dup2(all->pipefd[0], 0);
		close(all->pipefd[0]);
		close(all->pipefd[1]);
	}
}

void	run_pipe(t_all *all)
{
	int	i;
	int	status;

	i = -1;
	all->fd_in = 0;
	status = 0;
	while (all->parts[++i])
	{
		if (all->parts[i + 1] == NULL)
			break ;
		if (pipe(all->pipefd) < 0)
			exit(EXIT_FAILURE);
		fork_pipe(all, i);
	}
	all->pipe_flag = 0;
	start_parsing(all, all->parts[i]);
	run_commands(all);
	dup2(all->fd_0, 0);
	dup2(all->fd_1, 1);
	while (all->pipe_count--)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
}
