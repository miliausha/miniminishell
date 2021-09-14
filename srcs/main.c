#include "minishell.h"

static void	term_settings(t_all *all, int status)
{
	tcgetattr(0, &all->s_term);
	if (status == 1)
	{
		all->s_term.c_lflag &= ~(ECHOCTL);
		tcsetattr(0, TCSANOW, &all->s_term);
	}
	else if (status == 0)
	{
		all->s_term.c_lflag |= (ECHOCTL);
		tcsetattr(0, TCSANOW, &all->s_term);
	}
}

static void	init(t_all *all, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	all->fd_0 = dup(0);
	all->fd_1 = dup(1);
	all->env = dup_env(env);
	if (!all->env)
		exit(EXIT_FAILURE);
	set_signals(0);
	all->words = NULL;
	all->arg = NULL;
	all->flag_redir = 0;
	all->redir_file = NULL;
	all->parts = NULL;
	g_exit = 0;
	all->flag_fd = 0;
	rl_outstream = stderr;
}

char	*get_line(t_all *all)
{
	char	*line;

	if (!all->env)
		return (NULL);
	line = readline("minishell$ ");
	if (!line)
	{
		ft_putendl_fd("exit", 2);
		rl_clear_history();
		term_settings(all, 0);
		free(line);
		free_arr((void **)all->env);
		exit(g_exit);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_all	all;

	init(&all, ac, av, env);
	term_settings(&all, 1);
	while (21)
	{
		line = get_line(&all);
		if (!preparser(line))
			parser(&all, line);
		free(line);
		line = NULL;
	}
	return (0);
}
