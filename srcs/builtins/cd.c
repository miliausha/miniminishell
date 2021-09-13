#include "minishell.h"

void	update_pwd(t_all *all)
{
	char	pwd[1000];
	char	*path;

	getcwd(pwd, 1000);
	path = env_path_search(all->env, "PWD=");
	update_env(all, "OLDPWD", path);
	free(path);
	update_env(all, "PWD", pwd);
	g_exit = 0;
}

void	go_home(t_all *all)
{
	char	*home_path;

	home_path = env_path_search(all->env, "HOME=");
	if (!home_path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_exit = 1;
		return ;
	}
	if (chdir(home_path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home_path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exit = 1;
		return ;
	}
	free(home_path);
	update_pwd(all);
}

void	tilda(t_all *all)
{
	char	*str;

	if (all->words[1][0] == '~')
	{
		str = ft_strtrim(all->words[1], "~");
		free(all->words[1]);
		all->words[1] = str;
	}
	if (chdir(all->words[1]))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(all->words[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exit = 1;
		return ;
	}
	update_pwd(all);
}

void	print_cd(t_all *all)
{
	if (!all->words[1])
		go_home(all);
	else
		tilda(all);
}
