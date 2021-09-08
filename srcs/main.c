#include "minishell.h"

static void	term_settings(t_all *all)
{
	tcgetattr(0, &all->s_term);
	all->s_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &all->s_term);
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
}

char	*get_line(t_all *all)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
		ft_exit(all);
	add_history(line);
	return (line);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_all	all;

	init(&all, ac, av, env);
	term_settings(&all);
	while (21)
	{
		line = get_line(&all);
		if (!preparser(line))
			parser(&all, line);
		free(line);
	}
	free(line);
	free_arr((void **)all.env);
	rl_clear_history();
	all.s_term.c_lflag |= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &all.s_term);
	return (0);
}
