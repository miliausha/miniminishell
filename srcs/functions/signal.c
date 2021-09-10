#include "minishell.h"

void	set_signals(int status)
{
	if (status)
	{
		signal(SIGINT, sigfunc_execve);
		signal(SIGQUIT, sigfunc_execve);
	}
	else
	{
		signal(SIGINT, sigfunc);
		signal(SIGQUIT, sigfunc);
	}
}

void	sigfunc_execve(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("^\\Quit: 3", 2);
		g_exit = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putendl_fd("^C", 2);
		g_exit = 130;
	}
}

void	sigfunc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("exit\n");
		exit (0);
	}
}
